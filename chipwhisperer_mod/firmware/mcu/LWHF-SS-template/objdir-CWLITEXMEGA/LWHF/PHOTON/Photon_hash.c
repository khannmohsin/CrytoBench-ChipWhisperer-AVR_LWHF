/* photon_test.c
 *
 * This program computes the PHOTON hash of a hardcoded plaintext
 * using different PHOTON variants and prints the hash values.
 *
 * Note: Ensure that 'photon.c' and 'photon.h' are available
 * and compiled along with this program.
 */

#include <stdio.h>
#include <string.h>
#include "photon.h"

int main() {
    /* Hardcoded plaintext */
    const char *plaintext = "This is a hardcoded plaintext message for PHOTON hashing.";

    /* Convert plaintext to byte array */
    const byte *message = (const byte *)plaintext;
    int message_bit_length = strlen(plaintext) * 8; // Length in bits

    /* Variables for digest */
    byte digest[DIGESTSIZE / 8]; // DIGESTSIZE is defined in photon.h

    /* Compute the hash */
    hash(digest, message, message_bit_length);

    /* Print the PHOTON variant being used */
    printf("PHOTON-%d Hash:\n", DIGESTSIZE);

    /* Print the plaintext */
    printf("Plaintext:\n%s\n\n", plaintext);

    /* Print the hash value in hexadecimal format */
    printf("Hash Value:\n");
    for (int i = 0; i < DIGESTSIZE / 8; ++i) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return 0;
}