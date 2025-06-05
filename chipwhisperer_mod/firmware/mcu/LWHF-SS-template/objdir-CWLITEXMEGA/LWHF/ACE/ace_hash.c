#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "ace.h"
#include "crypto_hash.h"
#include "api.h"

// Define a hardcoded message
const char *hardcoded_message = "This is a hardcoded message to be hashed using ACE-Hash256.";

int main() {
    unsigned char digest[CRYPTO_BYTES]; // Buffer to store the hash output
    unsigned long long message_len = strlen(hardcoded_message); // Get the length of the message

    // Print the message to be hashed
    printf("Message: %s\n", hardcoded_message);

    // Call the ACE-Hash256 function
    if (crypto_hash(digest, (const unsigned char *)hardcoded_message, message_len) != 0) {
        fprintf(stderr, "Hash computation failed!\n");
        return EXIT_FAILURE;
    }

    // Print the resulting hash
    printf("Hash: ");
    for (int i = 0; i < CRYPTO_BYTES; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}