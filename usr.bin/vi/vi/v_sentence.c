/*-
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
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
static char sccsid[] = "@(#)v_sentence.c	8.7 (Berkeley) 8/26/93";
#endif /* not lint */

#include <sys/types.h>

#include <ctype.h>

#include "vi.h"
#include "vcmd.h"

/*
 * In historic vi, a sentence was delimited by a '.', '?' or '!' character
 * followed by TWO spaces or a newline.  One or more empty lines was also
 * treated as a separate sentence.  The Berkeley documentation for historical
 * vi states that any number of ')', ']', '"' and '\'' characters can be
 * between the delimiter character and the spaces or end of line, however,
 * the historical implementation did not handle additional '"' characters.
 * We follow the documentation here, not the implementation.
 *
 * Once again, historical vi didn't do sentence movements associated with
 * counts consistently, mostly in the presence of lines containing only
 * white-space characters.
 *
 * This implementation also permits a single tab to delimit sentences, and
 * treats lines containing only white-space characters as empty lines.
 * And, tabs are eaten (along with spaces) when skipping to the start of the
 * text follow a "sentence".
 */

/*
 * v_sentencef -- [count])
 *	Move forward count sentences.
 */
int
v_sentencef(sp, ep, vp, fm, tm, rp)
	SCR *sp;
	EXF *ep;
	VICMDARG *vp;
	MARK *fm, *tm, *rp;
{
	enum { BLANK, NONE, PERIOD } state;
	VCS cs;
	u_long cnt;

	cs.cs_lno = fm->lno;
	cs.cs_cno = fm->cno;
	if (cs_init(sp, ep, &cs)) 
		return (1);

	cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1;

	/*
	 * If in white-space, the next start of sentence counts as one.
	 * This may not handle "  .  " correctly, but it's real unclear
	 * what correctly means in that case.
	 */
	if (cs.cs_flags == CS_EMP || cs.cs_flags == 0 && isblank(cs.cs_ch)) {
		if (cs_fblank(sp, ep, &cs))
			return (1);
		if (--cnt == 0) {
			if (fm->lno != cs.cs_lno || fm->cno != cs.cs_cno)
				goto okret;
			return (1);
		}
	}
	for (state = NONE;;) {
		if (cs_next(sp, ep, &cs))
			return (1);
		if (cs.cs_flags == CS_EOF)
			break;
		if (cs.cs_flags == CS_EOL) {
			if ((state == PERIOD || state == BLANK) && --cnt == 0) {
				if (cs_next(sp, ep, &cs))
					return (1);
				if (cs.cs_flags == 0 &&
				    isblank(cs.cs_ch) && cs_fblank(sp, ep, &cs))
					return (1);
				goto okret;
			}
			state = NONE;
			continue;
		}
		if (cs.cs_flags == CS_EMP) {	/* An EMP is two sentences. */
			if (--cnt == 0)
				goto okret;
			if (cs_fblank(sp, ep, &cs))
				return (1);
			if (--cnt == 0)
				goto okret;
			state = NONE;
			continue;
		}
		switch (cs.cs_ch) {
		case '.':
		case '?':
		case '!':
			state = PERIOD;
			break;
		case ')':
		case ']':
		case '"':
		case '\'':
			if (state != PERIOD)
				state = NONE;
			break;
		case '\t':
			if (state == PERIOD)
				state = BLANK;
			/* FALLTHROUGH */
		case ' ':
			if (state == PERIOD) {
				state = BLANK;
				break;
			}
			if (state == BLANK && --cnt == 0) {
				if (cs_fblank(sp, ep, &cs))
					return (1);
				goto okret;
			}
			/* FALLTHROUGH */
		default:
			state = NONE;
			break;
		}
	}

	/* EOF is a movement sink. */
	if (fm->lno != cs.cs_lno || fm->cno != cs.cs_cno)
		goto okret;
	v_eof(sp, ep, NULL);
	return (1);

okret:	rp->lno = cs.cs_lno;
	rp->cno = cs.cs_cno;

	/*
	 * Historic, uh, features, yeah, that's right, call 'em features.
	 * If the sentence movement is cutting an entire line, the buffer
	 * is in line mode.  Reach up into the caller's VICMDARG structure,
	 * and whack the flags.
	 */
	if (F_ISSET(vp, VC_C | VC_D | VC_Y) &&
	    fm->cno == 0 && (rp->cno == 0 || cs.cs_flags != 0)) {
		if (rp->cno == 0)
			--rp->lno;
		F_SET(vp, VC_LMODE);
	}
	return (0);
}

/*
 * v_sentenceb -- [count](
 *	Move backward count sentences.
 */
int
v_sentenceb(sp, ep, vp, fm, tm, rp)
	SCR *sp;
	EXF *ep;
	VICMDARG *vp;
	MARK *fm, *tm, *rp;
{
	VCS cs;
	recno_t slno;
	size_t len, scno;
	u_long cnt;
	int last1, last2;

	if (fm->lno == 1 && fm->cno == 0) {
		v_sof(sp, NULL);
		return (1);
	}

	cs.cs_lno = fm->lno;
	cs.cs_cno = fm->cno;
	if (cs_init(sp, ep, &cs))
		return (1);

	cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1;

	/*
	 * If on an empty line, skip to the next previous
	 * non-white-space character.
	 */
	if (cs.cs_flags == CS_EMP) {
		if (cs_bblank(sp, ep, &cs))
			return (1);
		for (;;) {
			if (cs_next(sp, ep, &cs))
				return (1);
			if (cs.cs_flags != CS_EOL)
				break;
		}
	}

	for (last1 = last2 = 0;;) {
		if (cs_prev(sp, ep, &cs))
			return (1);
		if (cs.cs_flags == CS_SOF)	/* SOF is a movement sink. */
			break;
		if (cs.cs_flags == CS_EOL) {
			last2 = last1;
			last1 = 1;
			continue;
		}
		if (cs.cs_flags == CS_EMP) {
			if (--cnt == 0)
				goto ret;
			if (cs_bblank(sp, ep, &cs))
				return (1);
			last1 = last2 = 0;
			continue;
		}
		switch (cs.cs_ch) {
		case '.':
		case '?':
		case '!':
			if (!last1 || --cnt != 0) {
				last2 = last1 = 0;
				continue;
			}

ret:			slno = cs.cs_lno;
			scno = cs.cs_cno;

			/*
			 * Move to the start of the sentence, skipping blanks
			 * and special characters.
			 */
			do {
				if (cs_next(sp, ep, &cs))
					return (1);
			} while (!cs.cs_flags &&
			    (cs.cs_ch == ')' || cs.cs_ch == ']' ||
			    cs.cs_ch == '"' || cs.cs_ch == '\''));
			if ((cs.cs_flags || isblank(cs.cs_ch)) &&
			    cs_fblank(sp, ep, &cs))
				return (1);

			/*
			 * If it was ".  xyz", with the cursor on the 'x', or
			 * "end.  ", with the cursor in the spaces, or the
			 * beginning of a sentence preceded by an empty line,
			 * we can end up where we started.  Fix it.
			 */
			if (fm->lno != cs.cs_lno || fm->cno != cs.cs_cno)
				goto okret;

			/*
			 * Well, if an empty line preceded possible blanks
			 * and the sentence, it could be a real sentence.
			 */
			for (;;) {
				if (cs_prev(sp, ep, &cs))
					return (1);
				if (cs.cs_flags == CS_EOL)
					continue;
				if (cs.cs_flags == 0 && isblank(cs.cs_ch))
					continue;
				break;
			}
			if (cs.cs_flags == CS_EMP)
				goto okret;

			/* But it wasn't; try again. */
			++cnt;
			cs.cs_lno = slno;
			cs.cs_cno = scno;
			last2 = last1 = 0;
			break;
		case '\t':
			last1 = last2 = 1;
			break;
		default:
			last2 = last1;
			last1 =
			    cs.cs_flags == CS_EOL || isblank(cs.cs_ch) ||
			    cs.cs_ch == ')' || cs.cs_ch == ']' ||
			    cs.cs_ch == '"' || cs.cs_ch == '\'' ? 1 : 0;
		}
	}

okret:	rp->lno = cs.cs_lno;
	rp->cno = cs.cs_cno;

	/*
	 * See comment in v_sentencef().  Ignore errors, they should
	 * never occur, and they'll get caught later.
	 */
	if (F_ISSET(vp, VC_C | VC_D | VC_Y) && rp->cno == 0 &&
	    file_gline(sp, ep, fm->lno, &len) != NULL && (len == 0 ||
	    fm->cno == len - 1))
		F_SET(vp, VC_LMODE);
	return (0);
}