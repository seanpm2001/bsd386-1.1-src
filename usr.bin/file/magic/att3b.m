#
# AT&T 3B machines
#
# The `versions' should be un-commented if they work for you.
# (Was the problem just one of endianness?)
#
# 3B20
#
0	beshort		0550		3b20 COFF executable
>12	belong		>0		not stripped
#>22	beshort		>0		- version %ld
0	beshort		0551		3b20 COFF executable (TV)
>12	belong		>0		not stripped
#>22	beshort		>0		- version %ld
#
# WE32K
#
0	beshort		0560		WE32000 COFF
>18	beshort		^00000020	object
>18	beshort		&00000020	executable
>12	belong		>0		not stripped
>18	beshort		^00010000	N/A on 3b2/300 w/paging
>18	beshort		&00020000	32100 required
>18	beshort		&00040000	and mau hardware required
>20	beshort		0407		(impure)
>20	beshort		0410		(pure)
>20	beshort		0413		(demand paged)
>20	beshort		0443		(target shared library)
>22	beshort		>0		- version %ld
0	beshort		0561		WE32000 COFF executable (TV)
>12	belong		>0		not stripped
#>18	beshort		&00020000	- 32100 required
#>18	beshort		&00040000	and mau hardware required
#>22	beshort		>0		- version %ld
#
# core file for 3b2 
0	string		\000\004\036\212\200	3b2 core file
>364	string		>\0		of '%s'
