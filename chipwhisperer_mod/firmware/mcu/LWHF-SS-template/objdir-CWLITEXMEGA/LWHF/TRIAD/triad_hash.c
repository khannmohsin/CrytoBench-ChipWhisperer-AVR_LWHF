#include <stdio.h>
#include <string.h>
#include "crypto_hash.h"

int main() {
    // Define a hardcoded message
    const unsigned char message[] = "This is a test message for the Triad hash function.";
    unsigned long long message_len = strlen((const char *)message);

    // Buffer to hold the hash output
    unsigned char hash_output[32]; // Assuming 32-byte hash output

    // Compute the hash
    if (crypto_hash(hash_output, message, message_len) != 0) {
        fprintf(stderr, "Error: Hash computation failed.\n");
        return 1;
    }

    // Print the hash output
    printf("Message: %s\n", message);
    printf("Hash: ");
    for (int i = 0; i < 32; i++) {
        printf("%02x", hash_output[i]);
    }
    printf("\n");

    return 0;
}