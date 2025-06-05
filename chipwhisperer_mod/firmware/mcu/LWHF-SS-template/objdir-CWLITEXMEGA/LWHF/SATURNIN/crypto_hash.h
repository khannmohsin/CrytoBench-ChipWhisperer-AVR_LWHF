#ifndef CRYPTO_HASH_H
#define CRYPTO_HASH_H

#include <stdint.h>
#include <stddef.h>

// Define the hash output length in bytes (256 bits = 32 bytes for Saturnin-Hash)
#define CRYPTO_BYTES 32

/**
 * @brief Computes the cryptographic hash of the input data using Saturnin-Hash.
 *
 * @param[out] out Pointer to the buffer where the hash output will be stored (length: CRYPTO_BYTES).
 * @param[in] in Pointer to the input data to be hashed.
 * @param[in] inlen Length of the input data in bytes.
 * @return 0 on success, non-zero on failure.
 */
int crypto_hash(unsigned char *out, const unsigned char *in, unsigned long long inlen);

#endif // CRYPTO_HASH_H