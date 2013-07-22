/*
 * #include "r4gfile_p2739cj2t4ppm2lhq3expnucx.h"
 *
 * Resource vector aware ANSI C library FILE* support.
 *
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */

#ifndef HEADER_P2739CJ2T4PPM2LHQ3EXPNUCX_INCLUDED
   #define HEADER_P2739CJ2T4PPM2LHQ3EXPNUCX_INCLUDED
   #ifdef __cplusplus
      extern "C" {
   #endif
   #include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
   #include <stdio.h>


   typedef struct r4gfile_vars *r4gfile;
   r4gfile r4gfile_open(r4g *xc, char const *filename, char const *mode);
   void r4gfile_seek(r4g *xc, r4gfile file, long offset, int whence);
   void r4gfile_read(
      r4g *xc, void *buffer, size_t unitsize, size_t units, r4gfile file
   );
   void r4gfile_write(
         r4g *xc, void const *buffer, size_t unitsize, size_t units
      ,  r4gfile file
   );
   void r4gfile_flush(r4g *xc, r4gfile file);

   #define R4GFILE_WRAP_AUTOCLOSE (1 << 0)
   #define R4GFILE_WRAP_AUTOFLUSH (1 << 1)
   r4gfile r4gfile_wrap(
      r4g *xc, FILE *stream, char const *streamname, int flags
   );


   #ifdef __cplusplus
      }
   #endif
#endif /* !HEADER_P2739CJ2T4PPM2LHQ3EXPNUCX_INCLUDED */
