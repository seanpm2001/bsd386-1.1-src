#
# Alliant FX series a.out files:
# If the FX series is the one that had a processor with a 68K-derived
# instruction set, the "short" should probably become "beshort" and the
# "long" should probably become "belong".
# If it's the i860-based one, they should probably become either the
# big-endian or little-endian versions, depending on the mode they ran
# the 860 in....
#
0	short		0420		0420 Alliant virtual executable
>2	short		&0x0020		common library
>16	long		>0		not stripped
0	short		0421		0421 Alliant compact executable
>2	short		&0x0020		common library
>16	long		>0		not stripped
