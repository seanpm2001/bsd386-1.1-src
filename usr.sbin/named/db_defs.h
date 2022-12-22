/*
 *	from db.h	4.16 (Berkeley) 6/1/90
 *	=Id: db_defs.h,v 1.4 1993/11/03 12:26:04 vixie Exp =
 */

/*
 * ++Copyright++ 1985, 1990
 * -
 * Copyright (c) 1985, 1990
 *    The Regents of the University of California.  All rights reserved.
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
 * 	This product includes software developed by the University of
 * 	California, Berkeley and its contributors.
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
 * -
 * Portions Copyright (c) 1993 by Digital Equipment Corporation.
 * 
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies, and that
 * the name of Digital Equipment Corporation not be used in advertising or
 * publicity pertaining to distribution of the document or software without
 * specific, written prior permission.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND DIGITAL EQUIPMENT CORP. DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL DIGITAL EQUIPMENT
 * CORPORATION BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 * -
 * --Copyright--
 */

/*
 * Global definitions for data base routines.
 */

#define INVBLKSZ	7	/* # of namebuf pointers per block */
#define INVHASHSZ	919	/* size of inverse hash table */

	/* max length of data in RR data field */
#define MAXDATA		2048

#define DB_ROOT_TIMBUF	3600
#define TIMBUF		300

/*
 * Hash table structures.
 */
struct databuf {
	struct databuf	*d_next;	/* linked list */
	u_int32_t	d_ttl;		/* time to live */
					/* if d_zone == DB_Z_CACHE, then
					 * d_ttl is actually the time when
					 * the record will expire.
					 * otherwise (for authoritative
					 * primary and secondary zones),
					 * d_ttl is the time to live.
					 */
#ifdef CRED
	u_char		d_flags;
	u_char		d_cred:2;	/* level of credibility */
	u_char		d_clev:6;
#else
	u_int16_t	d_flags;
#endif
	int16_t		d_zone;		/* zone number */
	int16_t		d_class;	/* class number */
	int16_t		d_type;		/* type number */
	int16_t		d_mark;		/* place to mark data */
	int16_t		d_size;		/* size of data area */
#ifdef NCACHE
	int16_t		d_rcode;	/* rcode added for negative caching */
#else
	int16_t		d_unused;	/* explicit struct padding */
#endif
	int16_t		d_rcnt;
	u_int32_t	d_nstime;	/* NS response time, milliseconds */
	u_char		d_data[1]; 	/* the data is malloc'ed to size */
};
#define DATASIZE(n) (sizeof(struct databuf) - 1 + n)

/*
 * d_flags definitions
 */
#define DB_F_HINT       0x01	/* databuf belongs to fcachetab */

#ifdef CRED
/*
 * d_cred definitions
 */
#define	DB_C_AUTH	3	/* authoritative answer - best */
#define	DB_C_ANSWER	2	/* non-authoritative answer */
#define	DB_C_ADDITIONAL	1	/* additional data */
#define	DB_C_CACHE	0	/* cache - worst */
#endif /*CRED*/

struct namebuf {
	char		*n_dname;	/* domain name */
	u_int		n_hashval;	/* hash value of n_dname */
	struct namebuf	*n_next;	/* linked list */
	struct databuf	*n_data;	/* data records */
	struct namebuf	*n_parent;	/* parent domain */
	struct hashbuf	*n_hash;	/* hash table for children */
};

#if INVQ
struct invbuf {
	struct invbuf	*i_next;	/* linked list */
	struct namebuf	*i_dname[INVBLKSZ]; /* domain name */
};
#endif

struct hashbuf {
	int		h_size;		/* size of hash table */
	int		h_cnt;		/* number of entries */
	struct namebuf	*h_tab[1];	/* malloc'ed as needed */
};
#define HASHSIZE(s) (s*sizeof(struct namebuf *) + 2*sizeof(int))

#define HASHSHIFT	3
#define HASHMASK	0x1f

/*
 * Flags to updatedb
 */
#define DB_NODATA	0x01	/* data should not exist */
#define DB_MEXIST	0x02	/* data must exist */
#define DB_DELETE	0x04	/* delete data if it exists */
#define DB_NOTAUTH	0x08	/* must not update authoritative data */
#define DB_NOHINTS      0x10	/* don't reflect update in fcachetab */

#define DB_Z_CACHE      (0)	/* cache-zone-only db_dump()  */
#define DB_Z_ALL        (-1)	/* normal db_dump() */

/*
 * Error return codes
 */
#define OK		0
#define NONAME		-1
#define NOCLASS		-2
#define NOTYPE		-3
#define NODATA		-4
#define DATAEXISTS	-5
#define NODBFILE	-6
#define TOOMANYZONES	-7
#define GOODDB		-8
#define NEWDB		-9
#define AUTH		-10
