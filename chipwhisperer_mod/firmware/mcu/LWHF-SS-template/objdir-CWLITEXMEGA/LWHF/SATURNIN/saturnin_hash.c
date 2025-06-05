#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "crypto_hash.h"
#include "api.h"

int main() {
    // Hardcoded message
    const char *message = "Saturnin hash test message";
    unsigned long long message_length = strlen(message);

    // Buffer to store the hash output
    unsigned char hash_output[CRYPTO_BYTES];

    // Compute the hash
    int result = crypto_hash(hash_output, (const unsigned char *)message, message_length);
    if (result != 0) {
        fprintf(stderr, "Error computing hash\n");
        return 1;
    }

    // Print the message
    printf("Message: %s\n", message);

    // Print the hash output
    printf("Hash: ");
    for (int i = 0; i < CRYPTO_BYTES; i++) {
        printf("%02x", hash_output[i]);
    }
    printf("\n");

    return 0;
}