#ifndef CRYPTO_HASH_H
#define CRYPTO_HASH_H

// Define the size of the output hash in bytes
#define CRYPTO_BYTES 32

/**
 * Computes the hash of the input message.
 *
 * @param out Pointer to the output buffer where the hash will be stored.
 *            The buffer must have space for at least CRYPTO_BYTES bytes.
 * @param in Pointer to the input message to be hashed.
 * @param inlen Length of the input message in bytes.
 * @return 0 on success, non-zero on failure.
 */
int crypto_hash(unsigned char *out, const unsigned char *in, unsigned long long inlen);

#endif // CRYPTO_HASH_H