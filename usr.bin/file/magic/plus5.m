#
#/etc/magic entries for Plus Five's UNIX MUMPS
#
# XXX - byte order?  Paging Hokey....
#
0	short		0x259		mumps avl global
>2	byte		>0		(V%d)
>6	byte		>0		with %d byte name
>7	byte		>0		and %d byte data cells
0	short		0x25a		mumps blt global
>2	byte		>0		(V%d)
>8	short		>0		- %d byte blocks
>15	byte		0x00		- P/D format
>15	byte		0x01		- P/K/D format
>15	byte		0x02		- K/D format
>15	byte		>0x02		- Bad Flags
