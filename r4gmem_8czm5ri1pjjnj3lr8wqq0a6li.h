/*
 * #include "r4gmem_8czm5ri1pjjnj3lr8wqq0a6li.h"
 *
 * Resource vector aware ANSI C library memory allocation support.
 *
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */

#ifndef HEADER_8CZM5RI1PJJNJ3LR8WQQ0A6LI_INCLUDED
   #define HEADER_8CZM5RI1PJJNJ3LR8WQQ0A6LI_INCLUDED
   #ifdef __cplusplus
      extern "C" {
   #endif
   #include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
   #include <stddef.h>


   void *r4g_malloc(r4g *xc, size_t bytes);
   char *r4g_strdup(r4g *xc, char const *ephemeral_string);

   void *r4ga_malloc(r4g *xc, size_t bytes);
   void *r4ga_realloc(r4g *xc, void *ptr, size_t new_size);


   #ifdef __cplusplus
      }
   #endif
#endif /* !HEADER_8CZM5RI1PJJNJ3LR8WQQ0A6LI_INCLUDED */
