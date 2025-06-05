/* Spongent_hash.c */

#include <stdio.h>
#include <string.h>
#include "spongent.h"

int main() {
    /* Hardcoded plaintext */
    const BitSequence *plaintext = (const BitSequence *)"This is a test message for SPONGENT hashing.";

    /* Calculate the length of the plaintext in bits */
    DataLength databitlen = strlen((const char *)plaintext) * 8;

    /* Hash output buffer */
    BitSequence hashval[hashsize / 8];

    /* Initialize the hash output buffer */
    memset(hashval, 0, sizeof(hashval));

    /* Compute the hash */
    if (SpongentHash(plaintext, databitlen, hashval) != SUCCESS) {
        printf("Error computing SPONGENT hash.\n");
        return 1;
    }

    /* Print the SPONGENT variant and hash */
    printf("SPONGENT-%d Hash:\n", hashsize);
    printf("Plaintext:\n%s\n\n", plaintext);
    printf("Hash Value:\n");
    for (int i = 0; i < hashsize / 8; ++i) {
        printf("%02X", hashval[i]);
    }
    printf("\n");

    return 0;
}