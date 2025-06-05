#include <stdio.h>
#include <string.h>
#include "crypto_hash.h"
#include "api.h"

int main() {
    unsigned char message[] = "Hello, Coral Hash!";
    unsigned long long message_length = strlen((char *)message);

    unsigned char hash[CRYPTO_BYTES];
    memset(hash, 0, CRYPTO_BYTES);

    if (crypto_hash(hash, message, message_length) != 0) {
        printf("Hash computation failed.\n");
        return 1;
    }

    printf("Message: %s\n", message);
    printf("Hash: ");
    for (int i = 0; i < CRYPTO_BYTES; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}