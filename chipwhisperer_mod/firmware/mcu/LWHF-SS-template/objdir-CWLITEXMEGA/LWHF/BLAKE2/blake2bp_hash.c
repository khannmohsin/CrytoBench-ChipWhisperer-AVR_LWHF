/****************************************************
 * blake2bp_hash.c
 *
 * Example program that uses BLAKE2bp to hash
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
    const char *message = "Hello from BLAKE2bp!";

    /* Buffer to hold the hash output (BLAKE2B_OUTBYTES = 64 by default) */
    uint8_t hash[BLAKE2B_OUTBYTES];

    /* Desired output length in bytes (1 <= outlen <= 64 for BLAKE2bp) */
    size_t outlen = 32;  /* example: use a 256-bit digest (32 bytes) */

    /* Compute BLAKE2bp hash (parallel variant of BLAKE2b) */
    if (blake2bp(hash, outlen, message, strlen(message), NULL, 0) < 0)
    {
        fprintf(stderr, "Error: blake2bp() failed.\n");
        return 1;
    }

    /* Print results */
    printf("Message: \"%s\"\n", message);
    printf("BLAKE2bp-%zu digest: ", outlen * 8);  /* Show bit length (e.g. 256) */
    print_hex(hash, outlen);
    printf("\n");

    return 0;
}