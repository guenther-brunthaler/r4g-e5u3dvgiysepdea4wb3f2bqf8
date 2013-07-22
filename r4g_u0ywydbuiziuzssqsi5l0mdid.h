/*
 * #include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
 *
 * Resource Vector - store resource metadata in a single growing array.
 *
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */

#ifndef HEADER_U0YWYDBUIZIUZSSQSI5L0MDID_INCLUDED
   #define HEADER_U0YWYDBUIZIUZSSQSI5L0MDID_INCLUDED
   #ifdef __cplusplus
      extern "C" {
   #endif
   #include <stddef.h>
   #include <stdint.h>


   typedef struct {
      int ok; /* < 0: query for exception, 0: exception, > 0: no exception. */
      unsigned suppressed_errors; /* Number of follow-up exceptions. */
      /* Hidden private fields follow in the actually allocated structure. */
   } r4g;

   typedef void (*r4g_deallocator)(r4g *xc, void *related_data);

   typedef struct  {
      r4g_deallocator cleanup;
      void *data;
   } r4g_resource;


   r4g *r4g_create(int error_exit_code);
   void r4g_replace_error_exit_code(r4g *xc, int error_exit_code);
   void r4g_add(r4g *xc, r4g_deallocator cleanup, void *related_data);
   size_t r4g_count(r4g *xc);
   void r4g_free(r4g *xc, size_t keep_num_resources);
   void r4g_forget(r4g *xc, size_t first_resource_index, size_t count);
   void r4g_assoc(
      r4g *xc, uint_least32_t const *rand_key, void *related_data
   );
   void *r4g_lookup(r4g *xc, uint_least32_t const *rand_key);
   void r4g_die(r4g *xc, char const *msg, ...);


   #ifdef __cplusplus
      }
   #endif
#endif /* !HEADER_U0YWYDBUIZIUZSSQSI5L0MDID_INCLUDED */
