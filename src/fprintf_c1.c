/*
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */


#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif
#include <stddef.h>
#include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
#include "r4gstdio_tsq4kr2x9qnr3sh1jgkaaf8qg.h"
#include <stdio.h>
#include <stdarg.h>


extern void r4ga_fprintf(r4g *xc, FILE *stream, char const *format, ...) {
   va_list arg;
   va_start(arg, format);
   r4ga_vfprintf(xc, stream, format, arg);
   va_end(arg);
}
