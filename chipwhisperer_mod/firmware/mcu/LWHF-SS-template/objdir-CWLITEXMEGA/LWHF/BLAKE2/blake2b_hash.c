/****************************************************
 * blake2_hash.c
 *
 * Example program that uses BLAKE2b to hash
 * a hardcoded message.
 ****************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
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
    const char *message = "Hello, world! This is a test of BLAKE2b.";

    /* Buffer to hold the hash output (BLAKE2B_OUTBYTES = 64 by default) */
    uint8_t hash[BLAKE2B_OUTBYTES];

    /* Desired output length in bytes (1 <= outlen <= 64 for BLAKE2b) */
    size_t outlen = 32;  /* example: use a 256-bit digest (32 bytes) */

    /* Compute BLAKE2b hash */
    if (blake2b(hash, outlen, message, strlen(message), NULL, 0) < 0)
    {
        fprintf(stderr, "Error: blake2b() failed.\n");
        return 1;
    }

    /* Print results */
    printf("Message: \"%s\"\n", message);
    printf("BLAKE2b-%zu digest: ", outlen * 8);  /* Show bit length (e.g. 256) */
    print_hex(hash, outlen);
    printf("\n");

    return 0;
}