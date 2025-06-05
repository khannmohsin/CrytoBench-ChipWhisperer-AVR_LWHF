/****************************************************
 * blake2xb_hash.c
 *
 * Example program that uses BLAKE2xb (XOF) to hash
 * a hardcoded message and produce a variable-length digest.
 ****************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
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
    const char *message = "Hello from BLAKE2xb! Extendable output in action.";

    /* Let's say we want a 96-byte (768-bit) digest, 
       demonstrating the XOF capability to produce more 
       output than the usual 64-byte (512-bit) limit of BLAKE2b. */
    size_t outlen = 96;  
    /* Buffer to hold the variable-length output */
    uint8_t *hash = malloc(outlen);
    if (!hash)
    {
        fprintf(stderr, "Error allocating memory for output.\n");
        return 1;
    }

    /* 
     * Compute BLAKE2xb hash (no key provided). 
     * BLAKE2xb can produce from 1 up to 2^32-1 bytes of output. 
     * Here, outlen = 96 is just an example.
     */
    if (blake2xb(hash, outlen, message, strlen(message), NULL, 0) < 0)
    {
        fprintf(stderr, "Error: blake2xb() failed.\n");
        free(hash);
        return 1;
    }

    /* Print the results */
    printf("Message: \"%s\"\n", message);
    printf("BLAKE2xb-%zu (XOF) digest:\n", outlen * 8);
    print_hex(hash, outlen);
    printf("\n");

    free(hash);
    return 0;
}