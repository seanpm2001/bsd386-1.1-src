# Sequent information updated by Don Dwiggins <atsun!dwiggins>.
# For Sequent's multiprocessor systems (incomplete).
0	lelong	0x00ea        	BALANCE NS32000 .o
>16	lelong	>0		not stripped
>124	lelong	>0		version %ld
0	lelong	0x10ea        	BALANCE NS32000 executable (0 @ 0)
>16	lelong  >0            	not stripped
>124	lelong	>0		version %ld
0	lelong	0x20ea        	BALANCE NS32000 executable (invalid @ 0)
>16	lelong  >0            	not stripped
>124	lelong	>0		version %ld
0	lelong	0x30ea        	BALANCE NS32000 standalone executable
>16	lelong  >0          	not stripped
>124	lelong	>0		version %ld
#
# Symmetry information added by Jason Merrill <jason@jarthur.claremont.edu>.
# Symmetry magic nums will not be reached if DOS COM comes before them;
# byte 0xeb is matched before these get a chance.
0	leshort	0x12eb		SYMMETRY i386 .o
>16	lelong	>0		not stripped
>124	lelong	>0		version %ld
0	leshort	0x22eb		SYMMETRY i386 executable (0 @ 0)
>16	lelong	>0		not stripped
>124	lelong	>0		version %ld
0	leshort	0x32eb		SYMMETRY i386 executable (invalid @ 0)
>16	lelong	>0		not stripped
>124	lelong	>0		version %ld
0	leshort	0x42eb		SYMMETRY i386 standalone executable
>16	lelong	>0		not stripped
>124	lelong	>0		version %ld
