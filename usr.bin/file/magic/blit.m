# 68K Blit stuff as seen from 680x0 machine
# Note that this 0407 conflicts with several other a.out formats...
#
# XXX - should this be redone with "be" and "le", so that it works on
# little-endian machines as well?  If so, what's the deal with
# "VAX-order" and "VAX-order2"?
#
#0	long		0407		68K Blit (standalone) executable
#0	short		0407		VAX-order2 68K Blit (standalone) executable
0	short		03401		VAX-order 68K Blit (standalone) executable
0	long		0406		68k Blit mpx/mux executable
0	short		0406		VAX-order2 68k Blit mpx/mux executable
0	short		03001		VAX-order 68k Blit mpx/mux executable
# Need more values for WE32 DMD executables.
# Note that 0520 is the same as COFF
#0	short		0520		tty630 layers executable
