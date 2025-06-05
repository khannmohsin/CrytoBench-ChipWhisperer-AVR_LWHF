#include <stdio.h>
#include <string.h>
#include "crypto_hash.h"
#include "api.h"

#define MESSAGE "ISAP Hash Test Message"
#define HASH_OUTPUT_SIZE CRYPTO_BYTES

int main() {
    // Hardcoded message
    const char *message = MESSAGE;
    unsigned long long message_length = strlen(message);

    // Buffer to store the hash output
    unsigned char hash_output[HASH_OUTPUT_SIZE];

    // Compute the hash
    if (crypto_hash(hash_output, (const unsigned char *)message, message_length) != 0) {
        fprintf(stderr, "Error: Hash computation failed.\n");
        return 1;
    }

    // Print the message
    printf("Message: %s\n", message);

    // Print the hash in hexadecimal format
    printf("Hash: ");
    for (int i = 0; i < HASH_OUTPUT_SIZE; i++) {
        printf("%02x", hash_output[i]);
    }
    printf("\n");

    return 0;
}