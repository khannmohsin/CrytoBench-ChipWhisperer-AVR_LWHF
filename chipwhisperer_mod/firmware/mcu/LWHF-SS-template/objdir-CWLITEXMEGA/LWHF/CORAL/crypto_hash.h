#ifndef CRYPTO_HASH_H
#define CRYPTO_HASH_H

#define CRYPTO_BYTES 32 // Output size in bytes (256 bits)

int crypto_hash(unsigned char *out, const unsigned char *in, unsigned long long inlen);

#endif // CRYPTO_HASH_H