// blake3_hash.c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "blake3.h"  // Make sure this header is accessible

int main(void) {
    // 1. Hardcoded message
    const char *message = "Hello from BLAKE3!";

    // 2. Initialize the hasher
    blake3_hasher hasher;
    blake3_hasher_init(&hasher);

    // 3. Feed the message into the hasher
    blake3_hasher_update(&hasher, message, strlen(message));

    // 4. Finalize to get the hash output (32 bytes by default)
    uint8_t hash_out[BLAKE3_OUT_LEN];  // BLAKE3_OUT_LEN = 32 bytes
    blake3_hasher_finalize(&hasher, hash_out, BLAKE3_OUT_LEN);

    // 5. Print the resulting hash in hexadecimal
    printf("Message: \"%s\"\n", message);
    printf("BLAKE3 digest (hex): ");
    for (size_t i = 0; i < BLAKE3_OUT_LEN; i++) {
        printf("%02x", hash_out[i]);
    }
    printf("\n");

    return 0;
}