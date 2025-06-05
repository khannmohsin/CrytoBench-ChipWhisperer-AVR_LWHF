#include <stdio.h>
#include <string.h>
#include "crypto_hash.h"
#include "api.h"

// Hardcoded message
const char *message = "This is a hardcoded test message.";

int main() {
    unsigned char digest[CRYPTO_BYTES];  // Buffer for the resulting hash
    unsigned long long message_len = strlen(message);

    // Perform the hashing
    if (crypto_hash(digest, (const unsigned char *)message, message_len) != 0) {
        fprintf(stderr, "Error: Hash computation failed.\n");
        return 1;
    }

    // Print the resulting hash
    printf("Message: %s\n", message);
    printf("Message Digest (Hex): ");
    for (size_t i = 0; i < CRYPTO_BYTES; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return 0;
}