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
#include "r4gfile_internals.h"


extern void r4gfile_write(
   r4g *xc, void const *buffer, size_t unitsize, size_t units, r4gfile file
) {
   if (fwrite(buffer, unitsize, units, file->handle) == units) return;
   r4g_die(xc, "Error writing to \"%s\"!", file->name);
}
