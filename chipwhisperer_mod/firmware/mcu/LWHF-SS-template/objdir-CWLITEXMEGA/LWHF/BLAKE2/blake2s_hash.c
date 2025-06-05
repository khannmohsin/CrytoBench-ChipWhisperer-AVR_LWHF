/****************************************************
 * blake2s_hash.c
 *
 * Example program that uses BLAKE2s to hash
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
    const char *message = "Hello from BLAKE2s!";

    /* Buffer to hold the hash output (BLAKE2S_OUTBYTES = 32 by default) */
    uint8_t hash[BLAKE2S_OUTBYTES];

    /*
     * Desired output length in bytes (1 <= outlen <= 32 for BLAKE2s).
     * We'll use 16 bytes (128-bit) just as an example here.
     * You can set this to up to 32 if you want a 256-bit hash.
     */
    size_t outlen = 16;  

    /* Compute BLAKE2s hash (unkeyed) */
    if (blake2s(hash, outlen, message, strlen(message), NULL, 0) < 0)
    {
        fprintf(stderr, "Error: blake2s() failed.\n");
        return 1;
    }

    /* Print results */
    printf("Message: \"%s\"\n", message);
    printf("BLAKE2s-%zu digest: ", outlen * 8);  /* Show bit length (e.g. 128) */
    print_hex(hash, outlen);
    printf("\n");

    return 0;
}