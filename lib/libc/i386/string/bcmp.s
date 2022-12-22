/*-
 * Copyright (c) 1993 Berkeley Software Design, Inc. All rights reserved.
 * The Berkeley Software Design Inc. software License Agreement specifies
 * the terms and conditions for redistribution.
 */

#include "DEFS.h"
#include "COPY.h"

#ifdef LIBC_SCCS
	.asciz	"BSDI $Id: bcmp.s,v 1.1 1993/11/12 10:24:46 donn Exp $"
#endif

/*
 * Compare two blocks of data b1 and b2 of length len.
 * Return nonzero iff the blocks differ.
 *
 * int bcmp(const void *b1, const void *b2, size_t len);
 */
ENTRY(bcmp)
	COPY_PROLOGUE()

	cld
	movl %ecx,%eax
	andl $3,%eax
	shrl $2,%ecx
	repe; cmpsl
	jne 1f
	movl %eax,%ecx
	repe; cmpsb
	jne 1f

	xorl %eax,%eax

2:
	COPY_EPILOGUE()

1:
	movl $1,%eax
	jmp 2b
