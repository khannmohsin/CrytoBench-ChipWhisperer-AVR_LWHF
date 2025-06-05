#ifndef CRYPTO_HASH_H
#define CRYPTO_HASH_H

#include <stddef.h>

// Size of the hash output in bytes
#define CRYPTO_BYTES 32

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Computes the hash of the given input message.
 *
 * @param[out] out The buffer to store the hash output (size: CRYPTO_BYTES).
 * @param[in] in The input message to hash.
 * @param[in] inlen The length of the input message in bytes.
 * @return 0 on success, non-zero on failure.
 */
int crypto_hash(unsigned char *out, const unsigned char *in, unsigned long long inlen);

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_HASH_H