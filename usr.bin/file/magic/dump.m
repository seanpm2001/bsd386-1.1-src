#
# magic.dump, dump file format. For new and old dump filesystems
#
# We specify both byte orders in order to recognize byte-swapped dumps.
#
24	belong	60012		new-fs dump file (big endian),
>4	bedate	x		Previous dump %s,
>8	bedate	x		This dump %s,
>12	belong	>0		Volume %ld,
>692	belong	0		Level zero, type:
>692	belong	>0		Level %d, type:
>0	belong	1		tape header,
>0	belong	2		beginning of file record,
>0	belong	3		map of inodes on tape,
>0	belong	4		continuation of file record,
>0	belong	5		end of volume,
>0	belong	6		map of inodes deleted,
>0	belong	7		end of medium (for floppy),
>676	string	>\0		Label %s,
>696	string	>\0		Filesystem %s,
>760	string	>\0		Device %s,
>824	string	>\0		Host %s,
>888	belong	>0		Flags %x

24	belong	60011		old-fs dump file (big endian),
#>4	bedate	x		Previous dump %s,
#>8	bedate	x		This dump %s,
>12	belong	>0		Volume %ld,
>692	belong	0		Level zero, type:
>692	belong	>0		Level %d, type:
>0	belong	1		tape header,
>0	belong	2		beginning of file record,
>0	belong	3		map of inodes on tape,
>0	belong	4		continuation of file record,
>0	belong	5		end of volume,
>0	belong	6		map of inodes deleted,
>0	belong	7		end of medium (for floppy),
>676	string	>\0		Label %s,
>696	string	>\0		Filesystem %s,
>760	string	>\0		Device %s,
>824	string	>\0		Host %s,
>888	belong	>0		Flags %x

24	lelong	60012		new-fs dump file (little endian),
>4	ledate	x		Previous dump %s,
>8	ledate	x		This dump %s,
>12	lelong	>0		Volume %ld,
>692	lelong	0		Level zero, type:
>692	lelong	>0		Level %d, type:
>0	lelong	1		tape header,
>0	lelong	2		beginning of file record,
>0	lelong	3		map of inodes on tape,
>0	lelong	4		continuation of file record,
>0	lelong	5		end of volume,
>0	lelong	6		map of inodes deleted,
>0	lelong	7		end of medium (for floppy),
>676	string	>\0		Label %s,
>696	string	>\0		Filesystem %s,
>760	string	>\0		Device %s,
>824	string	>\0		Host %s,
>888	lelong	>0		Flags %x

24	lelong	60011		old-fs dump file (little endian),
#>4	ledate	x		Previous dump %s,
#>8	ledate	x		This dump %s,
>12	lelong	>0		Volume %ld,
>692	lelong	0		Level zero, type:
>692	lelong	>0		Level %d, type:
>0	lelong	1		tape header,
>0	lelong	2		beginning of file record,
>0	lelong	3		map of inodes on tape,
>0	lelong	4		continuation of file record,
>0	lelong	5		end of volume,
>0	lelong	6		map of inodes deleted,
>0	lelong	7		end of medium (for floppy),
>676	string	>\0		Label %s,
>696	string	>\0		Filesystem %s,
>760	string	>\0		Device %s,
>824	string	>\0		Host %s,
>888	lelong	>0		Flags %x
