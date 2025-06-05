#include <stdio.h>
#include <string.h>
#include "crypto_hash.h"
#include "api.h"

#define MESSAGE "Hello, Subterranean!"
#define MESSAGE_LENGTH (sizeof(MESSAGE) - 1)  // Exclude null terminator
#define HASH_OUTPUT_LENGTH 32  // Length of the hash output in bytes
int main() {
    unsigned char hash_output[HASH_OUTPUT_LENGTH];  // Buffer for the hash output

    // Hardcoded message
    const unsigned char message[] = MESSAGE;

    // Print the original message
    printf("Original Message: %s\n", MESSAGE);

    // Compute the hash using crypto_hash
    int result = crypto_hash(hash_output, message, MESSAGE_LENGTH);

    // Check for errors
    if (result != 0) {
        fprintf(stderr, "Error: crypto_hash failed with error code %d\n", result);
        return 1;
    }

    // Print the hash output
    printf("Hash Output: ");
    for (size_t i = 0; i < HASH_OUTPUT_LENGTH; i++) {
        printf("%02x", hash_output[i]);
    }
    printf("\n");

    return 0;
}