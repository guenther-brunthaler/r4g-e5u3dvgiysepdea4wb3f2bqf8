/*
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the GPLv3.
 */


#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif
#include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
#include "r4gstdio_tsq4kr2x9qnr3sh1jgkaaf8qg.h"
#include <stdio.h>


extern void r4ga_putchar(r4g *xc, int c) {
   if (putchar(c) == c) return;
   r4g_die(xc, "Error writing character %#x to standard output!", c);
}
