#include <stdio.h>
#include "crypto_hash.h"

int main() {
    const unsigned char message[] = "Hello, SivTempPhotonHash!";
    unsigned long long message_len = sizeof(message) - 1;
    unsigned char hash[CRYPTO_BYTES];

    if (crypto_hash(hash, message, message_len) == 0) {
        printf("Hash: ");
        for (size_t i = 0; i < CRYPTO_BYTES; i++) {
            printf("%02x", hash[i]);
        }
        printf("\n");
    } else {
        printf("Error computing hash.\n");
    }

    return 0;
}