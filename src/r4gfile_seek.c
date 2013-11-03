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


extern void r4gfile_seek(r4g *xc, r4gfile file, long offset, int whence) {
   if (!fseek(file->handle, offset, whence)) return;
   r4g_die(
         xc
      ,  "Seek error in \"%s\" for offset %ld relative to %s!"
      ,  file->name, offset
      ,  whence == SEEK_SET
         ?  "begin"
         :  whence == SEEK_END ? "end" : "current position"
   );
}
