#include <stdio.h>
#include <string.h>
#include "crypto_hash.h"
#include "api.h"

int main() {
    // Hardcoded message
    const unsigned char message[] = "Hello, DryGascon Hash!";
    unsigned long long message_length = strlen((const char *)message);

    // Buffer for the hash output
    unsigned char hash[CRYPTO_BYTES] = {0};

    // Compute the hash
    if (crypto_hash(hash, message, message_length) != 0) {
        printf("Hash computation failed.\n");
        return 1;
    }

    // Print the results
    printf("Message: %s\n", message);
    printf("Hash: ");
    for (int i = 0; i < CRYPTO_BYTES; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}