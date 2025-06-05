#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "crypto_hash.h"

#define MESSAGE "This is a hardcoded message for Xoodyak hash."

int main() {
    unsigned char digest[crypto_hash_BYTES]; // Buffer to store the hash output
    const char *message = MESSAGE;          // Hardcoded message
    unsigned long long message_len = strlen(message); // Length of the message

    // Print the message to be hashed
    printf("Message: %s\n", message);

    // Call the Xoodyak hash function
    if (crypto_hash(digest, (const unsigned char *)message, message_len) != 0) {
        fprintf(stderr, "Hash computation failed!\n");
        return EXIT_FAILURE;
    }

    // Print the resulting hash
    printf("Hash: ");
    for (int i = 0; i < crypto_hash_BYTES; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}