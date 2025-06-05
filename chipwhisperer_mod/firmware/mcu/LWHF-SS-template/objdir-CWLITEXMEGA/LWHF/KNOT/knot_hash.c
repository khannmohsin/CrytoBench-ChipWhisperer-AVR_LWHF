#include <stdio.h>
#include <string.h>
#include "api.h"
#include "crypto_hash.h"

int main() {
    // Hardcoded input message
    const char message[] = "This is a test message for the Knot hash function.";
    unsigned char digest[CRYPTO_BYTES];  // Buffer to store the hash digest

    // Compute the hash using the Knot hash function
    if (crypto_hash(digest, (const unsigned char *)message, strlen(message)) != 0) {
        fprintf(stderr, "Error: Hash computation failed.\n");
        return 1;
    }

    // Print the original message
    printf("Message: %s\n", message);

    // Print the resulting hash digest in hexadecimal format
    printf("Hash Digest: ");
    for (size_t i = 0; i < CRYPTO_BYTES; i++) {
        printf("%02X", digest[i]);
    }
    printf("\n");

    return 0;
}