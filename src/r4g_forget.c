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
#include <string.h>


/*
 * Remove resource vector entries without invoking their cleanup functions.
 * This can be used to remove temporary deallocators once the final
 * deallocators are ready to be added.
 *
 * This function will never fail (at least not without crashing the whole
 * application) and never reallocate memory.
 */
extern void r4g_forget(r4g *xc, size_t first_resource_index, size_t count) {
   struct r4g_internal *fc= (struct r4g_internal *)xc;
   (void)memmove(
         fc->resources + first_resource_index
      ,  fc->resources + first_resource_index + count
      ,     ((fc->num_resources-= count) - first_resource_index)
         *  sizeof *fc->resources
   );
}
