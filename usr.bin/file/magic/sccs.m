# SCCS archive structure:
# \001h01207
# \001s 00276/00000/00000
# \001d D 1.1 87/09/23 08:09:20 ian 1 0
# \001c date and time created 87/09/23 08:09:20 by ian
# \001e
# \001u
# \001U
# ... etc.
# Now '\001h' happens to be the same as the 3B20's a.out magic number (0550).
# *Sigh*. And these both came from various parts of the USG.
# Maybe we should just switch everybody from SCCS to RCS!
# Further, you can't just say '\001h0', because the five-digit number
# is a checksum that could (presumably) have any leading digit,
# and we don't have regular expression matching yet. 
# Hence the following official kludge:
8	string		\001s\ 			SCCS archive.
