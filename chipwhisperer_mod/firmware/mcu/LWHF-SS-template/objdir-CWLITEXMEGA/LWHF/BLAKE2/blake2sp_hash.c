/****************************************************
 * blake2sp_hash.c
 *
 * Example program that uses BLAKE2sp to hash
 * a hardcoded message in parallel.
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
    const char *message = "Hello from BLAKE2sp in parallel!";

    /* Buffer to hold the hash output (BLAKE2S_OUTBYTES = 32 by default) */
    uint8_t hash[BLAKE2S_OUTBYTES];

    /*
     * Desired output length in bytes (1 <= outlen <= 32 for BLAKE2s).
     * We'll use 32 bytes (256-bit) to get a full BLAKE2s-sized digest.
     */
    size_t outlen = 32;

    /*
     * The BLAKE2sp function can process data in parallel using multiple 
     * internal BLAKE2s states. If compiled with OpenMP, it can leverage 
     * multiple threads. Otherwise, it runs in a serial "striped" mode.
     */
    if (blake2sp(hash, outlen, message, strlen(message), NULL, 0) < 0)
    {
        fprintf(stderr, "Error: blake2sp() failed.\n");
        return 1;
    }

    /* Print results */
    printf("Message: \"%s\"\n", message);
    printf("BLAKE2sp-%zu digest: ", outlen * 8);  /* Show bit length (e.g. 256) */
    print_hex(hash, outlen);
    printf("\n");

    return 0;
}