#! /bin/sh
# Generate immutable static variables suitable as <rand_key> arguments for
# r4g_assoc() and r4g_lookup(). A list of identifiers to be defined can be
# specified as arguments. Defaults to "name".
#
# (c) 2013 by Guenther Brunthaler.
# This source file is free software.
# Distribution is permitted under the terms of the LGPLv3.
   
RANDOM_SOURCE=/dev/urandom
test -n "$1" || set -- name
for name
do
head -c4 "$RANDOM_SOURCE" | od -An -vtx4 | sed -e '
		s, ,0x,
		s,\(.*\),static uint_least32_t const '"$name"'= UINT32_C(\1);,
	'
done
