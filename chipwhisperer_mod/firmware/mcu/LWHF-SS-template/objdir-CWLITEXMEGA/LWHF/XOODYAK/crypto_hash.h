#ifndef CRYPTO_HASH_H
#define CRYPTO_HASH_H

#include <stddef.h>

// Define the output size of the hash function
#define crypto_hash_BYTES 32

// Function prototype for the crypto hash function
int crypto_hash(unsigned char *out, const unsigned char *in, unsigned long long inlen);

#endif // CRYPTO_HASH_H