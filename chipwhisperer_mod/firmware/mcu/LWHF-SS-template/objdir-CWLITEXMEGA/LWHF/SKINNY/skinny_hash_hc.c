#include <stdio.h>
#include <string.h>
#include "crypto_hash.h"
#include "api.h"

#define MESSAGE "This is a hardcoded test message."

int main() {
    // Hardcoded message
    const unsigned char message[] = MESSAGE;
    unsigned long long message_len = strlen((const char *)message);

    // Output buffer for the hash
    unsigned char hash[CRYPTO_BYTES];

    // Hash the message
    if (crypto_hash(hash, message, message_len) != 0) {
        fprintf(stderr, "Hashing failed.\n");
        return 1;
    }

    // Print the hash in hexadecimal format
    printf("Message: %s\n", message);
    printf("Hash: ");
    for (size_t i = 0; i < CRYPTO_BYTES; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}