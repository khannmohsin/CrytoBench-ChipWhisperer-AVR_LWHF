#ifndef CRYPTO_HASH_H
#define CRYPTO_HASH_H

#include <stdint.h>
#include <stddef.h>

// Define the length of the hash output in bytes
#define CRYPTO_BYTES 32

// Function prototype for the hash function
int crypto_hash(
    unsigned char *out,                  // Output hash buffer
    const unsigned char *in,             // Input message
    unsigned long long inlen             // Input message length in bytes
);

#endif // CRYPTO_HASH_H