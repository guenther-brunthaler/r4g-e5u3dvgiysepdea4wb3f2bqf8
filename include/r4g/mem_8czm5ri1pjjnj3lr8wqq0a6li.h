/*
 * #include <r4g/mem_8czm5ri1pjjnj3lr8wqq0a6li.h>
 *
 * R4G aware ANSI C library memory allocation support.
 *
 * Version 2020.19
 * (c) 2013-2020 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */

#ifndef HEADER_8CZM5RI1PJJNJ3LR8WQQ0A6LI_INCLUDED
   #define HEADER_8CZM5RI1PJJNJ3LR8WQQ0A6LI_INCLUDED

   #include <r4g/r4g_u0ywydbuiziuzssqsi5l0mdid.h>
   #include <stddef.h>

   #ifdef __cplusplus
      extern "C" {
   #endif

   /* Exception-throwing wrappers for libc memory allocation functions. */
   void *o2_malloc_c1(size_t bytes);
   void *o6_realloc_c1(void *ptr_o5, size_t new_size);
   char *o2_strdup_c1(char const *ephemeral_string_o0);

   /* Transfer the responsibility for eventual deallocation of a buffer
    * already allocated via malloc() to the resource list by registering a
    * destructor for it there. Returns the address within the resource list
    * object where the pointer to the buffer is stored. This allows the buffer
    * to be reallocated with updating the pointer which will eventually by used
    * by the destructor. */
   void **free_later_c5(void *mallocated_o1);
   /* Allocate a memory block which does not need resizing and register a
    * destructor for it in the resource list. */
   void *o0_malloc_c5(size_t bytes);

   #ifdef __cplusplus
      }
   #endif
#endif /* !HEADER_8CZM5RI1PJJNJ3LR8WQQ0A6LI_INCLUDED */
