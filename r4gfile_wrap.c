/*
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */


#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif
#include <stdlib.h>
#include <string.h>
#include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
#include "r4gfile_internals.h"
#include "r4gmem_8czm5ri1pjjnj3lr8wqq0a6li.h"


extern void r4gfile_flush(r4g *xc, r4gfile file) {
   if (!fflush(file->handle)) return;
   r4g_die(xc, "Could not write back buffer to file \"%s\"!", file->name);
}


static void r4ga_fclose(r4g *xc, void *data) {
   r4gfile f= (r4gfile)data;
   if (!fclose(f->handle)) return;
   r4g_die(xc, "Could not close file \"%s\"!", f->name);
}


static void add_destructors(r4g *xc, r4gfile file, int flags) {
   if (flags & R4GFILE_WRAP_AUTOCLOSE) r4g_add(xc, r4ga_fclose, file);
   if (flags & R4GFILE_WRAP_AUTOFLUSH) {
      r4g_add(xc, (r4g_deallocator)r4gfile_flush, file);
   }
}


extern r4gfile r4gfile_wrap(
   r4g *xc, FILE *stream, char const *streamname, int flags
) {
   struct r4gfile_vars tmp;
   size_t forget_from, forget_count;
   r4gfile file;
   forget_from= r4g_count(xc);
   tmp.handle= stream;
   tmp.name= streamname;
   add_destructors(xc, &tmp, flags); /* Temporarily on the stack. */
   forget_count= r4g_count(xc) - forget_from;
   (file= r4g_malloc(xc, sizeof *file))->name= r4g_strdup(xc, streamname);
   if (!(file->handle= stream)) {
      r4g_die(xc, "Stream \"%s\" has not been opened!", streamname);
   }
   r4g_forget(xc, forget_from, forget_count);
   /* Final version is dynamically allocated. */
   add_destructors(xc, file, flags);
   return file;
}
