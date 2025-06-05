#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "photon.h"
#include "beetle.h"
#include "crypto_hash.h"

int main() {
    // Hardcoded message
    const char *message = "This is a test message for Photon-Beetle hashing.";
    unsigned long long message_len = strlen(message);

    // Output buffer for the hash (digest)
    unsigned char digest[CRYPTO_BYTES];

    // Compute the hash
    if (crypto_hash(digest, (const unsigned char *)message, message_len) != 0) {
        printf("Error: Hash computation failed.\n");
        return -1;
    }

    // Print the message and the hash
    printf("Message: %s\n", message);
    printf("Message Digest (Hex):\n");
    for (size_t i = 0; i < CRYPTO_BYTES; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return 0;
}