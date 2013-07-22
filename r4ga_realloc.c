/*
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */


#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif
#include <stdlib.h>
#include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
#include "r4gmem_8czm5ri1pjjnj3lr8wqq0a6li.h"


extern void *r4ga_realloc(r4g *xc, void *ptr, size_t new_size) {
   if (!(ptr= realloc(ptr, new_size)) == !new_size) return ptr;
   r4g_die(xc, "Memory %s error!", !new_size ? "deallocation" : "allocation");
}
