#include <stdio.h>
#include <string.h>
#include "crypto_hash.h"

// Define the hardcoded message
#define MESSAGE "Hello, SPARKLE!"
#define MESSAGE_LENGTH (sizeof(MESSAGE) - 1) // Exclude the null terminator

int main() {
    unsigned char hash_output[crypto_hash_BYTES]; // Buffer for the hash output
    const unsigned char *message = (unsigned char *)MESSAGE; // Hardcoded message

    // Print the original message
    printf("Original Message: %s\n", message);

    // Perform hashing
    if (crypto_hash(hash_output, message, MESSAGE_LENGTH) != 0) {
        fprintf(stderr, "Hashing failed.\n");
        return 1;
    }

    // Print the hash output
    printf("Hash Output: ");
    for (size_t i = 0; i < crypto_hash_BYTES; i++) {
        printf("%02x", hash_output[i]);
    }
    printf("\n");

    return 0;
}