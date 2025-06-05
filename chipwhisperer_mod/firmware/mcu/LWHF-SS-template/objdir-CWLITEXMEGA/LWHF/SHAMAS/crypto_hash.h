#ifndef CRYPTO_HASH_H
#define CRYPTO_HASH_H

#include <stddef.h>

#define CRYPTO_BYTES 32 // Define the output length of the hash in bytes

int crypto_hash(unsigned char *out, const unsigned char *in, unsigned long long inlen);

#endif // CRYPTO_HASH_H