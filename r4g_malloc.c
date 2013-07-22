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


extern void *r4ga_malloc(r4g *xc, size_t bytes) {
   void *p;
   if (!(p= malloc(bytes))) {
      r4g_die(
         xc, "Failed to allocate %lu bytes of memory!", (unsigned long)bytes
      );
   }
   return p;
}


static void r4ga_free(r4g *xc, void *related_data) {
   (void)xc;
   free(related_data);
}


extern void *r4g_malloc(r4g *xc, size_t bytes) {
   void *p;
   r4g_add(xc, &r4ga_free, p= r4ga_malloc(xc, bytes));
   return p;
}
