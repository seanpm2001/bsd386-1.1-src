/*	BSDI $Id: pwd_mkdb.c,v 1.6 1994/01/31 22:56:03 sanders Exp $	*/

/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef lint
char copyright[] =
"@(#) Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "@(#)pwd_mkdb.c	5.5 (Berkeley) 5/6/91";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <db.h>
#include <pwd.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	INSECURE	1
#define	SECURE		2
#define	PERM_INSECURE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
#define	PERM_SECURE	(S_IRUSR|S_IWUSR)

char *progname = "pwd_mkdb";

static enum state { FILE_INSECURE, FILE_ORIG, FILE_SECURE } clean;
static struct passwd pwd;			/* password structure */
static char *pname;				/* password file name */
static int defcache = 1024 * 1024;		/* default cache size */
static int protodir = 0;			/* write file in . */

char *protoname __P((char *));
int scan __P((FILE *, struct passwd *));
void error __P((char *));
void cleanup __P((void));
void mv __P((char *, char *));
void usage __P((void));

main(argc, argv)
	int argc;
	char **argv;
{
	register int len, makeold;
	register char *p, *t;
	FILE *fp, *oldfp;
	DB *dp, *edp;
	struct sigaction act;
	struct sigaction oact;
	DBT data, key;
	int ch, cnt, tfd;
	char buf[MAX(MAXPATHLEN, LINE_MAX * 2)], tbuf[1024];
	unsigned long uid;
	unsigned long gid;
	HASHINFO openinfo;

	/* defaults */
	openinfo.cachesize = defcache;
	openinfo.nelem = 0;
	openinfo.bsize = 0;
	openinfo.ffactor = 0;
	openinfo.hash = NULL;
	openinfo.lorder = 0;

	makeold = 0;
	while ((ch = getopt(argc, argv, "c:dpv")) != EOF)
		switch (ch) {
		case 'c':			/* specify cache size (in K) */
			openinfo.cachesize = atoi(optarg) * 1024;
			break;
		case 'd':			/* write output files in . */
			protodir = 1;
			break;
		case 'p':			/* create V7 "/etc/passwd" */
			makeold = 1;
			break;
		case 'v':			/* backward compatible */
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	/*
	 * Setup signal handlers.  We ignore signals if they are already
	 * ignored, otherwise we call cleanup (which exits).
	 */
	act.sa_handler = cleanup;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGHUP);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGQUIT);
	sigaddset(&act.sa_mask, SIGTERM);
	sigaddset(&act.sa_mask, SIGTSTP);
	act.sa_flags = 0;
	sigaction(SIGHUP, &act, &oact);
	if (oact.sa_handler == SIG_IGN)
		sigaction(SIGHUP, &oact, (struct sigaction *)NULL);
	sigaction(SIGINT, &act, &oact);
	if (oact.sa_handler == SIG_IGN)
		sigaction(SIGINT, &oact, (struct sigaction *)NULL);
	sigaction(SIGQUIT, &act, &oact);
	if (oact.sa_handler == SIG_IGN)
		sigaction(SIGQUIT, &oact, (struct sigaction *)NULL);
	sigaction(SIGTERM, &act, &oact);
	if (oact.sa_handler == SIG_IGN)
		sigaction(SIGTERM, &oact, (struct sigaction *)NULL);
	sigaction(SIGTSTP, &act, &oact);
	if (oact.sa_handler == SIG_IGN)
		sigaction(SIGTSTP, &oact, (struct sigaction *)NULL);

	pname = *argv;
	/* Open the original password file */
	if (!(fp = fopen(pname, "r")))
		error(pname);

	/* Open the temporary insecure password database. */
	(void)sprintf(buf, "%s.tmp", protoname(_PATH_MP_DB));
	(void)unlink(buf);
	clean = FILE_INSECURE;
	dp = dbopen(buf, O_RDWR|O_CREAT|O_EXCL, PERM_INSECURE, DB_HASH, &openinfo);
	if (!dp)
		error(buf);

	/*
	 * Open file for old password file.  Minor trickiness -- don't want to
	 * chance the file already existing, since someone (stupidly) might
	 * still be using this for permission checking.  So, open it first and
	 * fdopen the resulting fd.  Don't really care who reads it.
	 */
	if (makeold) {
		(void)sprintf(buf, "%s.orig", protoname(pname));
		(void)unlink(buf);
		clean = FILE_ORIG;
		if ((tfd = open(buf,
		    O_WRONLY|O_CREAT|O_EXCL, PERM_INSECURE)) < 0)
			error(buf);
		if (!(oldfp = fdopen(tfd, "w")))
			error(buf);
	}

	/*
	 * The databases actually contain three copies of the original data.
	 * Each password file entry is converted into a rough approximation
	 * of a ``struct passwd'', with the strings placed inline.  This
	 * object is then stored as the data for three separate keys.  The
	 * first key * is the pw_name field prepended by the _PW_KEYBYNAME
	 * character.  The second key is the pw_uid field prepended by the
	 * _PW_KEYBYUID character.  The third key is the line number in the
	 * original file prepended by the _PW_KEYBYNUM character.  (The special
	 * characters are prepended to ensure that the keys do not collide.)
	 */
	data.data = (u_char *)buf;
	key.data = (u_char *)tbuf;
	for (cnt = 1; scan(fp, &pwd); ++cnt) {
#define	COMPACT(e)	t = e; while (*p++ = *t++);
		/* Create insecure data. */
		uid = pwd.pw_uid;	/* force a particular size */
		gid = pwd.pw_gid;
		p = buf;
		COMPACT(pwd.pw_name);
		COMPACT("*");
		bcopy((char *)&uid, p, sizeof(uid));
		p += sizeof(int);
		bcopy((char *)&gid, p, sizeof(gid));
		p += sizeof(int);
		bcopy((char *)&pwd.pw_change, p, sizeof(time_t));
		p += sizeof(time_t);
		COMPACT(pwd.pw_class);
		COMPACT(pwd.pw_gecos);
		COMPACT(pwd.pw_dir);
		COMPACT(pwd.pw_shell);
		bcopy((char *)&pwd.pw_expire, p, sizeof(time_t));
		p += sizeof(time_t);
		data.size = p - buf;

		/* Store insecure by name. */
		tbuf[0] = _PW_KEYBYNAME;
		len = strlen(pwd.pw_name);
		bcopy(pwd.pw_name, tbuf + 1, len);
		key.size = len + 1;
		if ((dp->put)(dp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");

		/* Store insecure by number. */
		tbuf[0] = _PW_KEYBYNUM;
		bcopy((char *)&cnt, tbuf + 1, sizeof(cnt));
		key.size = sizeof(cnt) + 1;
		if ((dp->put)(dp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");

		/* Store insecure by uid. */
		tbuf[0] = _PW_KEYBYUID;
		bcopy((char *)&uid, tbuf + 1, sizeof(uid));
		key.size = sizeof(uid) + 1;
		if ((dp->put)(dp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");
	}
	(void)(dp->close)(dp);

	/* Open the temporary encrypted password database. */
	(void)sprintf(buf, "%s.tmp", protoname(_PATH_SMP_DB));
	(void)unlink(buf);
	clean = FILE_SECURE;
	edp = dbopen(buf, O_RDWR|O_CREAT|O_EXCL, PERM_SECURE, DB_HASH, &openinfo);
	if (!edp)
		error(buf);

	rewind(fp);
	for (cnt = 1; scan(fp, &pwd); ++cnt) {
		/* Create secure data. */
		uid = pwd.pw_uid;	/* force a particular size */
		gid = pwd.pw_gid;
		p = buf;
		COMPACT(pwd.pw_name);
		COMPACT(pwd.pw_passwd);
		bcopy((char *)&uid, p, sizeof(uid));
		p += sizeof(int);
		bcopy((char *)&gid, p, sizeof(gid));
		p += sizeof(int);
		bcopy((char *)&pwd.pw_change, p, sizeof(time_t));
		p += sizeof(time_t);
		COMPACT(pwd.pw_class);
		COMPACT(pwd.pw_gecos);
		COMPACT(pwd.pw_dir);
		COMPACT(pwd.pw_shell);
		bcopy((char *)&pwd.pw_expire, p, sizeof(time_t));
		p += sizeof(time_t);
		data.size = p - buf;

		/* Store secure by name. */
		tbuf[0] = _PW_KEYBYNAME;
		len = strlen(pwd.pw_name);
		bcopy(pwd.pw_name, tbuf + 1, len);
		key.size = len + 1;
		if ((dp->put)(edp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");

		/* Store secure by number. */
		tbuf[0] = _PW_KEYBYNUM;
		bcopy((char *)&cnt, tbuf + 1, sizeof(cnt));
		key.size = sizeof(cnt) + 1;
		if ((dp->put)(edp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");

		/* Store secure by uid. */
		tbuf[0] = _PW_KEYBYUID;
		bcopy((char *)&uid, tbuf + 1, sizeof(uid));
		key.size = sizeof(uid) + 1;
		if ((dp->put)(edp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");

		/* Create original format password file entry */
		if (makeold)
			(void)fprintf(oldfp, "%s:*:%d:%d:%s:%s:%s\n",
			    pwd.pw_name, pwd.pw_uid, pwd.pw_gid, pwd.pw_gecos,
			    pwd.pw_dir, pwd.pw_shell);
	}
	(void)(edp->close)(edp);
	if (makeold) {
		(void)fsync(oldfp);
		(void)fclose(oldfp);
	}

	(void)sigprocmask(SIG_BLOCK, &act.sa_mask, (sigset_t *)NULL);

	/* Set master.passwd permissions, in case caller forgot. */
	(void)fchmod(fileno(fp), S_IRUSR|S_IWUSR);
	(void)fclose(fp);

	/* Install as the real password files. */
	(void)sprintf(buf, "%s.tmp", protoname(_PATH_MP_DB));
	mv(buf, protoname(_PATH_MP_DB));
	(void)sprintf(buf, "%s.tmp", protoname(_PATH_SMP_DB));
	mv(buf, protoname(_PATH_SMP_DB));
	if (makeold) {
		(void)sprintf(buf, "%s.orig", protoname(pname));
		mv(buf, protoname(_PATH_PASSWD));
	}
	/*
	 * Move the master password LAST -- chpass(1), passwd(1) and vipw(8)
	 * all use flock(2) on it to block other incarnations of themselves.
	 * The rename means that everything is unlocked, as the original file
	 * can no longer be accessed.
	 */
	mv(pname, protoname(_PATH_MASTERPASSWD));
	exit(0);
}

/*
 * This removes any leading path information
 * from a path if protodir is enabled.
 */
char *
protoname (s)
	char *s;
{
	char *p = s;

	if (protodir) {
	    	p = rindex(s, '/');
		p = (p ? p+1 : s);		/* skip past '/' if found */
	}
	return p;
}

scan(fp, pw)
	FILE *fp;
	struct passwd *pw;
{
	static int lcnt;
	static char line[LINE_MAX];
	char *p;

	if (!fgets(line, sizeof(line), fp))
		return(0);
	++lcnt;
	/*
	 * ``... if I swallow anything evil, put your fingers down my
	 * throat...'' -- The Who
	 */
	if (!(p = index(line, '\n'))) {
		(void)fprintf(stderr, "pwd_mkdb: line too long\n");
		goto fmt;

	}
	*p = '\0';
	if (!pw_scan(line, pw)) {
		(void)fprintf(stderr, "pwd_mkdb: at line #%d.\n", lcnt);
fmt:		errno = EFTYPE;
		error(pname);
		exit(1);
	}
}

void
mv(from, to)
	char *from, *to;
{
	int sverrno;
	char buf[MAXPATHLEN];

	if (rename(from, to)) {
		sverrno = errno;
		(void)sprintf(buf, "%s to %s", from, to);
		errno = sverrno;
		error(buf);
	}
}

void
error(name)
	char *name;
{
	(void)fprintf(stderr, "pwd_mkdb: %s: %s\n", name, strerror(errno));
	cleanup();
}

void
cleanup()
{
	char buf[MAXPATHLEN];

	switch(clean) {
	case FILE_SECURE:
		(void)sprintf(buf, "%s.tmp", protoname(_PATH_SMP_DB));
		(void)unlink(buf);
		/* FALLTHROUGH */
	case FILE_ORIG:
		(void)sprintf(buf, "%s.orig", protoname(pname));
		(void)unlink(buf);
		/* FALLTHROUGH */
	case FILE_INSECURE:
		(void)sprintf(buf, "%s.tmp", protoname(_PATH_MP_DB));
		(void)unlink(buf);
	}
	exit(1);
}

void
usage()
{
	(void)fprintf(stderr,
	    "usage: pwd_mkdb [-c cachesize] [-d] [-p] file\n");
	exit(1);
}
