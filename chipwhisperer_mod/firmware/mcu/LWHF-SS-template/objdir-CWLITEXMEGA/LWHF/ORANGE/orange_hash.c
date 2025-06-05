#include <stdio.h>
#include <string.h>
#include "crypto_hash.h"
#include "api.h"  // Ensure this includes CRYPTO_BYTES

int main() {
    // Define the hardcoded input message
    const char message[] = "This is a test message for the Orange hash function.";
    unsigned char digest[CRYPTO_BYTES];  // Buffer to store the resulting hash

    // Compute the hash using the Orange hash function
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