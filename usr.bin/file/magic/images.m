# image formats, originally from jef@helios.ee.lbl.gov (Jef Poskanzer),
# additions by janl@ifi.uio.no as well as others. Jan also suggested
# merging several one- and two-line files into here.
#
# XXX - byte order for GIF and TIFF fields?
#

0	string		xbtoa			btoa'd file

# PBMPLUS
0	string		P1			PBM file
0	string		P2			PGM file
0	string		P3			PPM file
0	string		P4			PBM "rawbits" file
0	string		P5			PGM "rawbits" file
0	string		P6			PPM "rawbits" file

# TIFF and friends
0	string		\115\115		TIFF file, big-endian
>2      short           >0              	version %d
0	string		\111\111		TIFF file, little-endian
>2      short           >0              	version %d
#
# NIFF (Navy Interchange File Format, a modification of TIFF)
0	string		IIN1			NIFF raster data

# GIF
0	string		GIF		GIF picture
>3	string		87a		- version %s
>3	string		89a		- version %s
>6	leshort		>0		%hd x
>8	leshort		>0		%hd,
>10	byte		&0x40		interlaced,
>10	byte&0x07	=0x00		2 colors
>10	byte&0x07	=0x01		4 colors
>10	byte&0x07	=0x02		8 colors
>10	byte&0x07	=0x03		16 colors
>10	byte&0x07	=0x04		32 colors
>10	byte&0x07	=0x05		64 colors
>10	byte&0x07	=0x06		128 colors
>10	byte&0x07	=0x07		256 colors

# Miscellany
0	long		1123028772		Artisan image file
>4	long		1	rectangular 24-bit image
>4	long		2	rectangular 8-bit image with colormap
>4      long            3	rectangular 32-bit image (24-bit with matte)
0	string		\361\0\100\273		CMU window manager bitmap
0	string		#FIG			FIG graphics savefile text
>6      string          2.1             	Version 2.1
>6      string          2.0             	Version 2.0
0	string		GKSM			GKS Metafile
8	string		ILBM			IFF ILBM file
0	string		yz			MGR bitmap
6	string		JFIF			JPEG picture
0       string          ARF_BEGARF      	PHIGS clear text archive
