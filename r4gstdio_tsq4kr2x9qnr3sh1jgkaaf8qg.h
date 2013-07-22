/*
 * #include "r4gstdio_tsq4kr2x9qnr3sh1jgkaaf8qg.h"
 *
 * Resource vector aware ANSI C library stdio support.
 *
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */

#ifndef HEADER_TSQ4KR2X9QNR3SH1JGKAAF8QG_INCLUDED
   #define HEADER_TSQ4KR2X9QNR3SH1JGKAAF8QG_INCLUDED
   #ifdef __cplusplus
      extern "C" {
   #endif
   #include <stdio.h>
   #include <stdarg.h>


   void r4ga_vprintf(r4g *xc, char const *format, va_list args);
   void r4ga_vfprintf(
      r4g *xc, FILE *stream, char const *format, va_list args
   );
   void r4ga_printf(r4g *xc, char const *format, ...);
   void r4ga_fprintf(r4g *xc, FILE *stream, char const *format, ...);
   void r4ga_fputs(r4g *xc, char const *s, FILE *stream);
   void r4ga_putchar(r4g *xc, int c);
   void r4ga_puts(r4g *xc, char const *s);


   #ifdef __cplusplus
      }
   #endif
#endif /* !HEADER_TSQ4KR2X9QNR3SH1JGKAAF8QG_INCLUDED */
