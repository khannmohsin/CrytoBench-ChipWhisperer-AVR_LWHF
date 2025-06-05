/****************************************************
 * blake2xs_hash.c
 *
 * Example program that uses BLAKE2xs (XOF) to hash
 * a hardcoded message and produce a variable-length digest.
 ****************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h> /* for malloc/free */
#include "blake2.h"

/* Helper function to print a byte array as hex */
static void print_hex(const uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; ++i)
        printf("%02x", data[i]);
}

int main(void)
{
    /* Hardcoded message */
    const char *message = "Hello from BLAKE2xs! Extendable output in action.";

    /*
     * BLAKE2xs can produce from 1 up to 65535 bytes (since outlen is a 16-bit field).
     * Here, we'll request a 64-byte (512-bit) digest for demo purposes.
     */
    size_t outlen = 64;  
    /* Buffer to hold the variable-length output */
    uint8_t *hash = (uint8_t *)malloc(outlen);
    if (!hash)
    {
        fprintf(stderr, "Error allocating memory for output.\n");
        return 1;
    }

    /*
     * Compute BLAKE2xs hash (no key provided). 
     * You can provide a key if desired (up to BLAKE2S_KEYBYTES in length).
     */
    if (blake2xs(hash, outlen, message, strlen(message), NULL, 0) < 0)
    {
        fprintf(stderr, "Error: blake2xs() failed.\n");
        free(hash);
        return 1;
    }

    /* Print the results */
    printf("Message: \"%s\"\n", message);
    printf("BLAKE2xs-%zu (XOF) digest:\n", outlen * 8);  /* bit length, e.g., 512 */
    print_hex(hash, outlen);
    printf("\n");

    free(hash);
    return 0;
}