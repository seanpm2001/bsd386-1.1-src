#
# magic.rs6000:
#
# RS/6000 and the RT PC.
#
0	beshort		0x01df		executable (RISC System/6000 V3.1) or obj module
>12	belong		>0		not stripped
# Breaks sun4 statically linked execs.
#0      beshort		0x0103		executable (RT Version 2) or obj module
#>2	byte		0x50		pure
#>28	belong		>0		not stripped
#>6	beshort		>0		- version %ld
0	beshort		0x0104		shared library
0	beshort		0x0105		ctab data
0	beshort		0xfe04		structured file
0	string		0xabcdef	message catalog
#0	string		<aiaff>		archive
