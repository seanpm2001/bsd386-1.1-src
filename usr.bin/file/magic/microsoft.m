#
# Microsoft (Xenix, not DOS)
#
# "Middle model" stuff, and "Xenix 8086 relocatable or 80286 small
# model" lifted from "magic.xenix", with comment "derived empirically;
# treat as folklore until proven"
#
# "small model", "large model", "huge model" stuff lifted from XXX
#
# XXX - "x.out" collides with PDP-11 archives....
#
0	string		core		core file (Xenix)
0	byte		0x80		8086 relocatable (Microsoft)
0	leshort		0xff65		x.out
>2	string		__.SYMDEF	 randomized
>0	byte		x		archive
0	leshort		0x206		Microsoft a.out
>8	leshort		1		Middle model
>0x1e	leshort		&0x10		overlay
>0x1e	leshort		&0x2		separate
>0x1e	leshort		&0x4		pure
>0x1e	leshort		&0x800		segmented
>0x1e	leshort		&0x400		standalone
>0x1e	leshort		&0x8		fixed-stack
>0x1c	byte		&0x80		byte-swapped
>0x1c	byte		&0x40		word-swapped
>0x10	lelong		>0		not-stripped
>0x1e	leshort		^0xc000		pre-SysV
>0x1c	byte		&0x4		86
>0x1c	byte		&0x9		286
>0x1c	byte		&0xa		386
>0x1f	byte		<0x040		small model
>0x1f	byte		=0x048		large model	
>0x1f	byte		=0x049		huge model 
>0x1e	leshort		&0x1		executable
>0x1e	leshort		^0x1		object file
>0x1e	leshort		&0x40		Large Text
>0x1e	leshort		&0x20		Large Data
>0x1e	leshort		&0x120		Huge Objects Enabled
>0x10	lelong		>0		not stripped

0	leshort		0x140		old Microsoft 8086 x.out
>0x3	byte		&0x4		separate
>0x3	byte		&0x2		pure
>0	byte		&0x1		executable
>0	byte		^0x1		relocatable
>0x14	lelong		>0		not stripped

0	lelong		0x206		b.out
>0x1e	leshort		&0x10		overlay
>0x1e	leshort		&0x2		separate
>0x1e	leshort		&0x4		pure
>0x1e	leshort		&0x800		segmented
>0x1e	leshort		&0x400		standalone
>0x1e	leshort		&0x1		executable
>0x1e	leshort		^0x1		object file
>0x1e	leshort		&0x4000		V2.3
>0x1e	leshort		&0x8000		V3.0
>0x1c	byte		&0x4		86
>0x1c	byte		&0xb		186
>0x1c	byte		&0x9		286
>0x1c	byte		&0x29		286
>0x1c	byte		&0xa		386
>0x1e	leshort		&0x4		Large Text
>0x1e	leshort		&0x2		Large Data
>0x1e	leshort		&0x102		Huge Objects Enabled

0	leshort		0x580		XENIX 8086 relocatable or 80286 small model
