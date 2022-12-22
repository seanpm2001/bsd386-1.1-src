/* 
Copyright (C) 1993 Free Software Foundation

This file is part of the GNU IO Library.  This library is free
software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option)
any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

As a special exception, if you link this library with files
compiled with a GNU compiler to produce an executable, this does not cause
the resulting executable to be covered by the GNU General Public License.
This exception does not however invalidate any other reasons why
the executable file might be covered by the GNU General Public License. */

/* This file defines a stdio-like environment, except that it avoid
   link-time name clashes with an existing stdio.
   It allows for testing the libio using stdio-using programs
   with an incompatible libc.a.
   It is not predantically correct - e.g. some macros are used
   that may evaluate a stream argument more than once.  */

#include "iolibio.h"

typedef _IO_FILE FILE;
#ifndef EOF
#define EOF (-1)
#endif
#ifndef BUFSIZ
#define BUFSIZ 1024
#endif

/* #define size_t, fpos_t L_tmpname TMP_MAX */

#define _IOFBF 0 /* Fully buffered. */
#define _IOLBF 1 /* Line buffered. */
#define _IONBF 2 /* No buffering. */

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define stdin _IO_stdin
#define stdout _IO_stdout
#define stderr _IO_stderr

#define getc(_fp) _IO_getc(_fp)
#define putc(_ch, _fp) _IO_putc(_ch, _fp)

#define clearerr _IO_clearerr
#define fclose _IO_fclose
#define feof _IO_feof
#define ferror _IO_ferror
#define fflush _IO_fflush
#define fgetc(__fp) _IO_getc(_fp)
#define fgetpos _IO_fgetpos
#define fgets _IO_fgets
#define fopen _IO_fopen
#define fprintf _IO_fprintf
#define fputc(_ch, _fp) _IO_putc(_ch, _fp)
#define fputs _IO_fputs
#define fread _IO_fread
#define freopen _IO_freopen
#define fscanf _IO_fscanf
#define fseek _IO_fseek
#define fsetpos _IO_fsetpos
#define ftell _IO_ftell
#define fwrite _IO_fwrite
#define gets _IO_gets
#define perror _IO_perror
#define printf _IO_printf
#define puts _IO_puts
#define remove ??? _ARGS((const char*))
#define rename ??? _ARGS((const char* _old, const char* _new))
#define rewind _IO_rewind
#define scanf _IO_scanf
#define setbuf _IO_setbuf
#define setbuffer ??? _ARGS((FILE*, char*, int))
#define setvbuf _IO_setvbuf
#define sprintf _IO_sprintf
#define sscanf _IO_sscanf
#define tmpfile ??? _ARGS((void))
#define tmpnam ??? _ARGS((char*))
#define ungetc _IO_ungetc
#define vfprintf _IO_vfprintf
#define vprintf(__fmt, __args) vfprintf(stdout, __fmt, __args)
#define vsprintf _IO_vsprintf

#if !defined(__STRICT_ANSI__) || defined(_POSIX_SOURCE)
#define fdopen _IO_fdopen
#define fileno _IO_fileno
#define popen _IO_popen
#define pclose _IO_pclose
#define setbuf _IO_setbuf
#define setlinebuf _IO_setlinebuf
#endif
