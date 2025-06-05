#include <stdio.h>
#include <string.h>
#include "crypto_hash.h"

int main()
{
    const char *message = "This is a hardcoded message for CLX-Hash.";
    unsigned char digest[32]; // Buffer for the 256-bit hash
    unsigned long long message_length = strlen(message);

    // Call the CLX-Hash function from hash.c
    if (crypto_hash(digest, (const unsigned char *)message, message_length) != 0) {
        printf("Error: Hash computation failed.\n");
        return 1;
    }

    // Print the original message
    printf("Message: %s\n", message);

    // Print the resulting hash in hexadecimal format
    printf("Hash: ");
    for (int i = 0; i < 32; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return 0;
}