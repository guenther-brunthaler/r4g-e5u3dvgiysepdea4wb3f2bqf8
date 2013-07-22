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


extern void r4ga_fputs(r4g *xc, char const *s, FILE *stream) {
   if (fputs(s, stream) >= 0) return;
   r4g_die(xc, "Error writing a string to a stream.");
}
