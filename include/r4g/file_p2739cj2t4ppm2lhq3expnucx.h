/*
 * #include <r4g/file_p2739cj2t4ppm2lhq3expnucx.h>
 *
 * R4G aware ANSI C library FILE* support.
 *
 * Version 2020.19
 * (c) 2013-2020 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */

#ifndef HEADER_P2739CJ2T4PPM2LHQ3EXPNUCX_INCLUDED
   #define HEADER_P2739CJ2T4PPM2LHQ3EXPNUCX_INCLUDED

   #include <r4g/r4g_u0ywydbuiziuzssqsi5l0mdid.h>
   #include <stdio.h>

   #ifdef __cplusplus
      extern "C" {
   #endif


   typedef struct r4gfile_vars *r4gfile;

   r4gfile r4gfile_open_c5(char const *filename, char const *mode);
   void r4gfile_seek_c1(r4gfile file, long offset, int whence);
   void r4gfile_read_c1(
      void *buffer, size_t unitsize, size_t units, r4gfile file
   );
   void r4gfile_write_c1(
      void const *buffer, size_t unitsize, size_t units, r4gfile file
   );
   void r4gfile_flush_c1(r4gfile file);

   #define R4GFILE_WRAP_AUTOCLOSE (1 << 0)
   #define R4GFILE_WRAP_AUTOFLUSH (1 << 1)
   r4gfile r4gfile_wrap_c5(FILE *stream, char const *streamname, int flags);


   #ifdef __cplusplus
      }
   #endif
#endif /* !HEADER_P2739CJ2T4PPM2LHQ3EXPNUCX_INCLUDED */
