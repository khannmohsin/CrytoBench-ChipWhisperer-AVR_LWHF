#ifndef CRYPTO_HASH_H
#define CRYPTO_HASH_H

// Define the size of the hash output (256 bits = 32 bytes)
#define CRYPTO_BYTES 32

// Function prototype for the CLX-Hash function
int crypto_hash(
    unsigned char *out,              // Output buffer for the hash (32 bytes)
    const unsigned char *in,         // Input message
    unsigned long long inlen         // Length of the input message in bytes
);

#endif // CRYPTO_HASH_H