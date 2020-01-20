/*
 * Version 2020.20
 * (c) 2013-2020 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */

#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif
#include <stddef.h>
#include <r4g/r4g_u0ywydbuiziuzssqsi5l0mdid.h>
#include <r4g/r4gstdio_tsq4kr2x9qnr3sh1jgkaaf8qg.h>
#include <stdio.h>

extern void fputs_c1(char const *s, FILE *stream) {
   if (fputs(s, stream) >= 0) return;
   error_c1("Error writing a string to a stream.");
}
