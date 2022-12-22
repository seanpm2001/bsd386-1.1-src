#
# "ar", for all kinds of archives.
#
# XXX - why are there multiple <ar> thingies?  Note that 0x213c6172 is
# "!<ar", so, for new-style (4.xBSD/SVR2andup) archives, we have:
#
# 0	string		!<arch>		current ar archive
# 0	long		0x213c6172	archive file
#
# and for SVR3.1 archives, we have:
#
# 0	string		\<ar>		System V Release 1 ar archive
# 0	string		=<ar>		archive
# 0	string		=<ar>		archive
#
# XXX - did Aegis really store shared libraries, breakpointed modules,
# and absolute code program modules in the same format as new-style
# "ar" archives?
#
0	string		!<arch>		current ar archive
>8	string		__.SYMDEF	random library
>0	belong		=65538		- pre SR9.5
>0	belong		=65539		- post SR9.5
>0	beshort		2		- object archive
>0	beshort		3		- shared library module
>0	beshort		4		- debug break-pointed module
>0	beshort		5		- absolute code program module
0	string		\<ar>		System V Release 1 ar archive
0	string		=<ar>		archive
#
# XXX - from "vax", which appears to collect a bunch of byte-swapped
# thingies, to help you recognize VAX files on big-endian machines;
# with "leshort", "lelong", and "string", that's no longer necessary....
#
# 0	long		0x3c61723e	VAX 5.0 archive
#
0	long		0x213c6172	archive file
0	lelong		0177555		very old VAX archive
0	leshort		0177555		very old PDP-11 archive
#
# XXX - "pdp" claims that 0177545 can have an __.SYMDEF member and thus
# be a random library (it said 0xff65 rather than 0177545).
#
0	lelong		0177545		old VAX archive
>8	string		__.SYMDEF	random library
0	leshort		0177545		old PDP-11 archive
>8	string		__.SYMDEF	random library
#
0	string		=<ar>		archive
#
# From "pdp":
#
0	lelong		0x39bed		PDP-11 old archive
0	lelong		0x39bee		PDP-11 4.0 archive
#
0	string		-h-		Software Tools format archive text
# "arc" archiver
0	byte		26		'arc' archive
>1	byte		0		(empty)
>1	byte		1		(old format)
# Rahul Dhesi's zoo archive format, from keith@cerberus.uchicago.edu.
20	long		0xdca7c4fd	Rahul Dhesi's "zoo" archive
# ZIP archiver
0	string		PK		zip archive file 
>4	byte		x		- version
>4	byte		10		1.0
>4	byte		20		2.0

2	string		-lh		LHarc archive data
>6	byte		x		type %c
>20	byte		x		- header level %d
# ARJ archive data from jason@jarthur.Claremont.EDU
0	leshort		0xea60		ARJ archive data
>5	byte		x		- version %d,
>8	byte		>0		flags:
>>8	byte		&0x04		multi-volume,
>>8	byte		&0x10		slash switched,
>>8	byte		&0x20		backup,
>34	string		x		original name: %s,
>7	byte		0		os: MS/DOS
>7	byte		1		os: PRIMOS
>7	byte		2		os: UNIX
>7	byte		3		os: Amiga
>7	byte		4		os: Macintosh
>7	byte		5		os: OS/2
>7	byte		6		os: Apple ][ GS
>7	byte		7		os: Atari ST
>7	byte		8		os: NeXT
>7	byte		9		os: VAX/VMS
>3	byte		>0		%d]
