/*
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */


#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif
#include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
#include "r4g_internals.h"


extern size_t r4g_count(r4g *xc) {
   struct r4g_internal *fc= (struct r4g_internal *)xc;
   return fc->num_resources;
}
