/* #include <r4g/r4g_u0ywydbuiziuzssqsi5l0mdid.h>
 *
 * Resource Control Framework for C, 4th Generation.
 *
 * If multi-threading support is required, the preprocessor symbol
 * ENABLE_THREADS_8Y802YFBJ3A8H763I3XID022D must be defined whenever this
 * header is being #included. This will make the <r4g>-variable thread-local
 * and will work for every C11/C18 (or better) compiler, whether or not it
 * supports <threads.h>. Otherwise, only one of the threads must use the R4G
 * framework.
 *
 * Version 2020.20
 * Copyright (c) 2016-2020 Guenther Brunthaler. All rights reserved.
 * 
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3. */

#ifndef HEADER_U0YWYDBUIZIUZSSQSI5L0MDID_INCLUDED
#define HEADER_U0YWYDBUIZIUZSSQSI5L0MDID_INCLUDED

#ifdef __cplusplus
   extern "C" {
#endif

/* The central data structure for the R4G framework. One instance exists per
 * application or thread. */
struct resource_context_4th_generation {
   /* The total number of errors which have occurred. A negative number means
    * at least that (negated) number of errors, expressing a saturated count
    * and avoiding that the number of errors shown gets too large. For
    * instance, the value -25 displayed as something like "25 or more errors"
    * makes your program look better than the value 25000 displayed as "25000
    * errors". A very primitive error display routine might choose only to
    * display this information and ignore any error messages that have also
    * been set. An even more primitive routine might just display "an error
    * has occurred" if this is non-zero and ignore everything else. This also
    * acts as the transaction status when resource destructors are called.
    * Zero means that incomplete transactional resources should be committed
    * rather than being rolled back. */
   int errors;
   /* The first error which has occurred. It must be statically allocated.
    * Optionally, a dynamically allocated error message may also have been set
    * which provides a "better" version of the same error message, such as
    * including more detail and follow-up error messages. If an error display
    * routine supports the dynamically allocated error message (which is
    * optional), it should display it instead of this static one. Otherwise,
    * or if there is an error while building the dynamic error message, the
    * static message will act as a fallback. If no error message has been set
    * at all, <errors> can still be reported as unspecific generic errors. */
   char const *static_error_message;
   /* Pointer to a dynamically allocated lookup table managed by r4g_put()
    * and r4g_get(). If it is null, r4g_put() will fail. The lookup table
    * can be used to store pointers to arbitrary data, acting as a generic
    * extension mechanism for associating arbitrary data with a resource
    * context beyond the fields already defined here. */
   struct r4g_env *env;
   /* Null if the resource list is empty, or the address within the last
    * resource list entry where the pointer to its associated destructor
    * function is stored. Destructors need to locate the resource to be
    * destroyed using this address. */
   void (**rlist)(void);
};

/* This is the one well-known variable that everyone in R4G will be using. */
extern
   #ifdef ENABLE_THREADS_8Y802YFBJ3A8H763I3XID022D
      _Thread_local
   #endif
   struct resource_context_4th_generation r4g
;

/* Defines a pointer variable to type resource_t and initializes it with a
 * pointer to the beginning of an object of type resource_t where <r4g.rlist>
 * is a pointer to the struct's component <dtor_member>, which must be a
 * pointer to the destructor function for the object. <var_eq> must be the
 * part of the variable definition after resource_t and before the
 * initialization value, such as "* my_ptr=".
 *
 * Example: R4G_DEFINE_INIT_RPTR(struct minimal_resource, *r=, dtor);
 *
 * Note that you need to also #include <stddef.h> for actually using this. */
#define R4G_DEFINE_INIT_RPTR(resource_t, var_eq, dtor_member) \
   resource_t var_eq (void *)( \
      (char *)r4g.rlist - offsetof(resource_t, dtor_member) \
   )

/* An example of a mimimal complete resource object. */
struct minimal_resource {
   void (*dtor)(void); /* Cleanup function for this resource. */
   void (**saved)(void); /* Saved <r4g.rlist> pointer of previous resource. */
};

/* Calls the destructor of the last entry in the specified resource list until
 * there are no more entries left. Destructors need to unlink their entries
 * from the resource list eventually, or this will become an endless loop.
 * Destructors are also free to abort this loop prematurely by performing
 * non-local jumps or calling exit(). Because destructors may refer to objects
 * allocated on the stack somewhere, a longjmp can only be performed safely if
 * the destructors of all resources created since the setjmp() have already
 * been invoked. */
void release_c1(void);

/* Like release_c1() but stop releasing when resource <stop_at> would be
 * released next. The means all resources registered after <stop_at> will be
 * released, but not <stop_at> itself. */
void release_after_c1(void (*stop_at)(void));

/* Like release_c1() but stop releasing after resource <last> has been
 * released, even if releasing <last> required multiple calls of its
 * destructor. This means <last> itself as well as all resourced registered
 * after it will be released. */
void release_until_c1(void (*last)(void));

/* Raise an error. <static_message> must be a statically allocated error
 * message or null. If <r4g.static_error_message> is null, it will be set to
 * <static_message>. Otherwise it will be ignored because follow-up errors are
 * not supposed to replace the original first error message. If a dynamic
 * error message has been created, and if the current build supports dynamic
 * error messages at all (which is optional), <static_message> will also be
 * appended to its current contents, separating both by an empty line unless
 * this would make it the first line of the combined dynamic error message. It
 * is quite common to call error_c1() with a null argument for unlikely errors
 * that will probably never happen. The error display routine might report
 * such errors as "generic", "internal", "unspecified", "anonymous" or
 * something similar. Another reason for a null argument is if the error
 * messages have already been set and should not be touched. In any case,
 * raising an error will increment the current error count, unless it is
 * already saturated. If and when the error count may become saturated is an
 * implementation detail of this function. If an error display routine
 * supports dynamic messages, which is optional, it shall display the dynamic
 * message (unless it is empty/unset) instead of the static message. However,
 * an error display routine might also ignore both kinds of error messages and
 * just display the number of errors which occurred. Or even simpler, it might
 * just report that "an error" has occurred without giving any additional
 * details. It is therfore unwise to only set a dynamic message, because an
 * error display routine might choose to ignore the dynamic message and never
 * display it. Then release_c1() will be called to release all resources,
 * which will also display the error message if an appropriate resource
 * destructor for this purpose has been allocated in the resource list before.
 * Finally, the application will be terminated by exiting with a return code
 * of EXIT_FAILURE. If a different return code is preferred, a resource for
 * this purpose must be allocated, and its destructor should call exit() with
 * the required return code. */
void error_c1(char const *static_message);

/* Associate an arbitrary pointer value <data> with a particular binary
 * lookup key in the <r4g.env> lookup table. The lookup table must already
 * exist.
 *
 * Note that the lookup table is not a hash table. It is like a hash table
 * without a hash function. This simplifies and speeds up things, but
 * requires the keys to be random as if they were the output of a hash
 * function.
 *
 * <bin_key> should therefore not be text but rather a null-terminated
 * array of bytes taken from /dev/random and put into the source code as a
 * null-terminated "C" string of octal escapes. This will minimize the
 * chance for lookup key collisions, which would be very bad, representing
 * a hard-to-find logic error in your program.
 *
 * The following POSIX shell command will generate and display a proper key
 * as a string literal:
 *
 * $ dd if=/dev/random bs=1 count=16|od -An -vto1|sed 's/ /\\/g;s/.*''/"&"/'
 *
 * This will output something like
 * "\162\041\037\303\112\022\230\210\050\262\236\146\073\332\106\317" which
 * would be a proper binary key argument. */
void r4g_put_c1(char const (*bin_key)[17], void *data);

/* Return the pointer value previously set by r4g_put() and the same key,
 * or return null if no entry with a matching key is present or if no
 * lookup table has been created yet. */
void *r4g_get_c0(char const (*bin_key)[17]);

/* Dynamically allocate a lookup table and set it as <r4g.env> which must
 * have been null before. This allows r4g_put_c1() to function. This will
 * also add a destructor to the resource list for deallocating the table
 * and resetting <r4g.env> back to null. */
void create_env_c5(void);

/* Programs which want to support dynamically allocated error messages in
 * addition to statically allocated ones must call this function as soon as
 * possible, because setting dynamic error messages will only be possible
 * afterwards. This function will implicitly call create_env_c5() if
 * <r4g.enc> is null. */
void create_dynamic_error_message_c5(void);

/* If create_dynamic_error_message_c5() has never been called or if the
 * current build does not support dynamic error messages, just do exactly the
 * same as error_c1(). Otherwise, also do exactly the same as error_c1() would
 * do, but stop at point where error_c1() would call release_c1() but return
 * instead. This allows the caller call add_error_message_c1() or to
 * post-process the dynamically allocated error message in some way before
 * actually raising the error by calling raise_error_c1(). */
void prepare_error_c1(char const *static_message);

/* Call this only if prepare_error_c1() actually returned. This will add an
 * error message as a new paragraph to the end of the dynamically allocated
 * error message, making it the concatenation of the original and all
 * follow-up error messages optionally up to some implementation-defined limit
 * after which any attempts to add more messages will be silently ignored. */
void add_error_message_c1(char const *error_message);

/* Continue doing the remainder what prepare_error_c1() would have done if
 * it had not returned but rather done the same as error_c1(). In other
 * words, calling prepare_error_c1() immediately followed by
 * raise_error_c1() is the same as calling error_c1(). But between both
 * calls, the dynamically allocated error message can be modified and
 * extended, such as by incrementally appending additional optional
 * information to it. */
void raise_error_c1(void);

/* Sets the static error message to null and sets the dynamic error message
 * (if it exists and is supported by the current build) to an empty string.
 * Finally, set the current error count to zero. Call this after an error
 * message has been displayed. */
void clear_error_c1(void);


#ifdef __cplusplus
   }
#endif
#endif /* !HEADER_U0YWYDBUIZIUZSSQSI5L0MDID_INCLUDED */
