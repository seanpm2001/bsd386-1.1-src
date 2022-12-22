#
# magic.encore: Recognize encore machines
#
# XXX - needs to have the byte order specified (NS32K was little-endian,
# dunno whether they run the 88K in little-endian mode or not).
#
0	short		0x154		Encore
>20	short		0x107		executable
>20	short		0x108		pure executable
>20	short		0x10b		demand-paged executable
>20	short		0x10f		unsupported executable
>12	long		>0		not stripped
>22	short		>0		- version %ld
>22	short		0		-
#>4	date		x		stamp %s
0	short		0x155		Encore unsupported executable
>12	long		>0		not stripped
>22	short		>0		- version %ld
>22	short		0		-
#>4	date		x		stamp %s
