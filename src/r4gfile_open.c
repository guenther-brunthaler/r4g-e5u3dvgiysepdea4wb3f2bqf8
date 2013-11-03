/*
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */


#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif
#include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
#include "r4gfile_internals.h"
#include <stdio.h>
#include <string.h>


extern r4gfile r4gfile_open(
   r4g *xc, char const *filename, char const *mode
) {
   FILE *handle;
   if (!(handle= fopen(filename, mode))) {
      r4g_die(xc, "Could not open file \"%s\"!", filename);
   }
   return r4gfile_wrap(
         xc
      ,  handle, filename
      ,  strchr(mode, '+') || strchr(mode, 'w') || strchr(mode, 'a')
         ?  R4GFILE_WRAP_AUTOCLOSE | R4GFILE_WRAP_AUTOFLUSH
         :  R4GFILE_WRAP_AUTOCLOSE
   );
}
