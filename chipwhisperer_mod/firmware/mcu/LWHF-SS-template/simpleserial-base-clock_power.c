// #define SS_VER SS_VER_2_1
#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simpleserial.h"
#include <stdbool.h>
#include <avr/io.h>


void delay_ms(uint32_t ms) {
    volatile uint32_t count;
    while (ms--) {
        for (count = 0; count < 4000; count++); // Adjust loop for timing
    }
}

// Example function to process the byte array
uint8_t* process_byte_array(uint8_t* input, uint8_t len) {
    if (strcmp((char*)input, "PHOTON") == 0) {

        #ifdef _HASH_FUNCTION_PHOTON_
        // Debugging
            // uint8_t plaintext[16] = "Photon Inside!";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);

            #include "photon.h"
            uint16_t digest_size = DIGESTSIZE;
            uint8_t digest[DIGESTSIZE / 8] = {0};
            uint8_t plaintext[16] = "Hello, World! :)";
            hash(digest, (const uint8_t*)plaintext, strlen(plaintext) * 8);

            // Validate the digest
            uint8_t empty_digest[DIGESTSIZE / 8] = {0};  // Reference for an empty digest
            if (memcmp(digest, empty_digest, sizeof(digest)) == 0) {
                // Digest is empty or invalid
                const char* error_msg = "Digest not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);
                exit(EXIT_FAILURE);  // Stops the program
                }

            // simpleserial_put('r', sizeof(digest), digest);
        #endif

    } else if (strcmp((char*)input, "QUARK") == 0) {

        #ifdef _HASH_FUNCTION_QUARK_
            // Debugging
            // uint8_t plaintext[16] = "QUARK Inside!";  // Example Debug Message
            // simpleserial_put('r', 16, plaintext);
    
            #include "quark.h" // Ensure the quark.h header is included
            #define MAXDIGEST 48

            u8 out[MAXDIGEST] = {0};
            const char *input_data = "Hello, World! :)";
            u64 input_length = strlen(input_data);
            int digest_size = 17;

            quark(out, (const u8 *)input_data, input_length);

            // simpleserial_put('r', 16, out);
        #endif

    } else if (strcmp((char*)input, "SPONGENT") == 0) {

        #ifdef _HASH_FUNCTION_SPONGENT_
        // Debugging
            // uint8_t plaintext[16] = "Spongent Inside!";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);
            #include "spongent.h"

            const BitSequence *plaintext = (const BitSequence *)"Hello, World! :)";
            DataLength databitlen = strlen((const char *)plaintext) * 8;
            BitSequence hashval[hashsize / 8];
            memset(hashval, 0, sizeof(hashval));
            SpongentHash(plaintext, databitlen, hashval);

            // Validate the digest
            BitSequence empty_hashval[hashsize / 8] = {0};  // Reference for an empty hash value
            if (memcmp(hashval, empty_hashval, sizeof(hashval)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);
                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }
            
            // simpleserial_put('r', sizeof(hashval), hashval);
        #endif

    } else if (strcmp((char*)input, "LESAMNTA") == 0) {

        #ifdef _HASH_FUNCTION_LESAMNTA_
        // Debugging
            // uint8_t plaintext[16] = "Lesamnta Inside!";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);
            #include "lesamnta-LW.h"

            const char *plaintext = "Hello, World! :)";
            const BitSequence *data = (const BitSequence *)plaintext;
            DataLength databitlen = strlen(plaintext) * 8;
            BitSequence hashval[LESAMNTALW_HASH_BITLENGTH / 8];
            HashReturn result = Hash(LESAMNTALW_HASH_BITLENGTH, data, databitlen, hashval);

            // Validate the hash
            BitSequence empty_hashval[LESAMNTALW_HASH_BITLENGTH / 8] = {0};
            if (memcmp(hashval, empty_hashval, sizeof(hashval)) == 0 ) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }
            // simpleserial_put('r', sizeof(hashval), hashval);
        #endif

    } else if (strcmp((char*)input, "ASCON") == 0) {

        #ifdef _HASH_FUNCTION_ASCON_
        // Debugging
            // uint8_t plaintext[16] = "Ascon Inside!";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);

            #include "api.h"
            #include "crypto_hash.h"

            const unsigned char message[] = "Hello, World! :)";
            unsigned char hash_output[CRYPTO_BYTES];
            int result = crypto_hash(hash_output, message, strlen((const char*)message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(hash_output, empty_hash_output, sizeof(hash_output)) == 0 || result != 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);
        #endif

    } else if (strcmp((char*)input, "PHOTON_BEETLE") == 0) {

        #ifdef _HASH_FUNCTION_PHOTON_BEETLE_
        // Debugging
            // uint8_t plaintext[16] = "Photon Beetle Inside!";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);

            #include "photon.h"
            #include "beetle.h"
            #include "crypto_hash.h"

            const char *message = "Hello, World! :)";
            unsigned long long message_len = strlen(message);
            unsigned char digest[CRYPTO_BYTES];
            int result = crypto_hash(digest, (const unsigned char *)message, message_len);

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "XOODYAK") == 0) {

        #ifdef _HASH_FUNCTION_XOODYAK_
        // Debugging
            // uint8_t plaintext[16] = "Xoodyak Inside!";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);

            #include "Xoodyak.h"

            const char *message = "Hello, World! :)";
            size_t message_len = strlen(message);

            uint8_t digest[32];  // Assuming a 256-bit hash (32 bytes)

            Xoodyak_Instance instance;
            Xoodyak_Initialize(&instance, NULL, 0, NULL, 0, NULL, 0);  // No key, ID, or counter for hashing

            Xoodyak_Absorb(&instance, (const uint8_t *)message, message_len);

            Xoodyak_Squeeze(&instance, digest, sizeof(digest));

            // Validate the hash
            uint8_t empty_digest[32] = {0};
            if (memcmp(digest, empty_digest, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', sizeof(digest), digest);

        #endif

    } else if (strcmp((char*)input, "KNOT") == 0) {

        #ifdef _HASH_FUNCTION_KNOT_
        // Debugging
            // uint8_t plaintext[16] = "Knot Inside!";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);

            #include "api.h"
            #include "crypto_hash.h"

            const char message[] = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];  // Buffer to store the hash digest

            // Compute the hash using the Knot hash function
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);         
        #endif
    }

    else if (strcmp((char*)input, "ORANGE") == 0) {

        #ifdef _HASH_FUNCTION_ORANGE_
        // Debugging
            // uint8_t plaintext[16] = "ORANGE Inside!";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);

            #include "crypto_hash.h"
            #include "api.h"

            const char message[] = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];  // Buffer to store the resulting hash

            // Compute the hash using the Orange hash function
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);


        #endif
    }

    else if (strcmp((char*)input, "SHAMAS") == 0) {

        #ifdef _HASH_FUNCTION_SHAMAS_
        // Debugging
            // uint8_t plaintext[16] = "Shamas Inside!";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);

            #include "crypto_hash.h"

            const unsigned char message[] = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];

            crypto_hash(digest, message, strlen((const char*)message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif
    }

    else if (strcmp((char*)input, "SIVRIJNDAEL") == 0) {

        #ifdef _HASH_FUNCTION_SIVRIJNDAEL_
        // Debugging
            // uint8_t plaintext[16] = "Sivrijndael Inside!";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);

            #include "crypto_hash.h"

            const unsigned char message[] = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];

            crypto_hash(digest, message, strlen((const char*)message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);


        #endif
    }

    else if (strcmp((char*)input, "SIVTEMPHOTON") == 0) {

        #ifdef _HASH_FUNCTION_SIVTEMPHOTON_
            #include "crypto_hash.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));
            // simpleserial_put('r', CRYPTO_BYTES, digest);

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "SKINNY") == 0) {

        #ifdef _HASH_FUNCTION_SKINNY_
            #include "crypto_hash.h"
            #include "api.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "SNEIK") == 0) {

        #ifdef _HASH_FUNCTION_SNEIK_
            #include "crypto_hash.h"
            #include "api.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "TRIAD") == 0) {

        #ifdef _HASH_FUNCTION_TRIAD_
            #include "crypto_hash.h"
            #include "api.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));
            // Validate the hash

            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "CORAL") == 0) {

        #ifdef _HASH_FUNCTION_CORAL_
            #include "crypto_hash.h"
            #include "api.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "GIMLI") == 0) {

        #ifdef _HASH_FUNCTION_GIMLI_
            #include "crypto_hash.h"
            #include "api.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);
            
        #endif

    } else if (strcmp((char*)input, "DRYGASCON") == 0) {

        #ifdef _HASH_FUNCTION_DRYGASCON_128_
        // Debugging
            // uint8_t plaintext[16] = "DRYGASCON 128";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);

            #include "crypto_hash.h"
            #include "api.h"

            const char message[] = "Hello, World! :)";
            unsigned long long message_length = strlen(message);

            unsigned char digest[CRYPTO_BYTES] = {0}; // Buffer for hash output
            crypto_hash(digest, (const unsigned char*)message, message_length);

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);
            
        #elif defined(_HASH_FUNCTION_DRYGASCON_256_)
        // Debugging
            // uint8_t plaintext[16] = "DRYGASCON 256";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);

            #include "crypto_hash.h"
            #include "api.h"

            const char message[] = "Hello, World! :)";
            unsigned long long message_length = strlen(message);

            unsigned char digest[CRYPTO_BYTES] = {0}; // Buffer for hash output
            crypto_hash(digest, (const unsigned char*)message, message_length);

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);


        #endif

    } else if (strcmp((char*)input, "CLX") == 0) {

        #ifdef _HASH_FUNCTION_CLX_
            #include "crypto_hash.h"
            // #include "api.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "ACE") == 0) {

        #ifdef _HASH_FUNCTION_ACE_
            #include "crypto_hash.h"
            #include "api.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "SPARKLE") == 0) {

        #ifdef _HASH_FUNCTION_SPARKLE_
            #include "crypto_hash.h"
            #include "api.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "SUBTERRAINEAN") == 0) {

        #ifdef _HASH_FUNCTION_SUBTERRAINEAN_
            #include "crypto_hash.h"
            #include "api.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "SATURNIN") == 0) {

        #ifdef _HASH_FUNCTION_SATURNIN_
            #include "api.h"
            #include "crypto_hash.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "ISAP") == 0) {

        #ifdef _HASH_FUNCTION_ISAP_
            #include "api.h"
            #include "crypto_hash.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);


                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif

    } else if (strcmp((char*)input, "GAGE") == 0) {

        #ifdef _HASH_FUNCTION_GAGE_
            #include "api.h"
            #include "crypto_hash.h"

            const char *message = "Hello, World! :)";
            unsigned char digest[CRYPTO_BYTES];
            crypto_hash(digest, (const unsigned char *)message, strlen(message));

            // Validate the hash
            unsigned char empty_hash_output[CRYPTO_BYTES] = {0};
            if (memcmp(digest, empty_hash_output, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', CRYPTO_BYTES, hash_output);

        #endif


    }else if (strcmp((char*)input, "BLAKE3") == 0) {

        #ifdef _HASH_FUNCTION_BLAKE3_
        // Debugging
            // uint8_t plaintext[16] = "Photon AEAD Inside!";  // Exactly 16 bytes
            // simpleserial_put('r', 16, plaintext);

            #include "blake3.h"

            const char *message = "Hello, World! :)";
            size_t message_len = strlen(message);

            uint8_t digest[BLAKE3_OUT_LEN];  // 32 bytes

            blake3_hasher hasher;
            blake3_hasher_init(&hasher);
            blake3_hasher_update(&hasher, message, message_len);
            blake3_hasher_finalize(&hasher, digest, BLAKE3_OUT_LEN);

            // Validate the hash
            uint8_t empty_digest[BLAKE3_OUT_LEN] = {0};
            if (memcmp(digest, empty_digest, sizeof(digest)) == 0) {
                // Hash is empty or invalid
                const char* error_msg = "Hash not found!";
                simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                // Terminate the program
                exit(EXIT_FAILURE);  // Stops the program
            }

            // If the hash is valid, continue the program
            // simpleserial_put('r', BLAKE3_OUT_LEN, digest);
        #endif
    }else if (strcmp((char*)input, "BLAKE2") == 0) {

        #ifdef _HASH_FUNCTION_BLAKE2s_
            // Debugging
                // uint8_t plaintext[16] = "Blake2s Inside!";  // Exactly 16 bytes
                // simpleserial_put('r', 16, plaintext);

                #include "blake2.h" 

                const char *message = "Hello, World! :)";
                size_t message_len = strlen(message);

                uint8_t digest[BLAKE2S_OUTBYTES];  // Buffer to hold the hash output

                size_t outlen = 32;  // Desired output length in bytes (1 <= outlen <= 32 for BLAKE2s)

                // Compute BLAKE2s hash (unkeyed)
                blake2s(digest, outlen, message, message_len, NULL, 0);

                // Validate the hash
                uint8_t empty_digest[BLAKE2S_OUTBYTES] = {0};
                if (memcmp(digest, empty_digest, outlen) == 0) {
                    // Hash is empty or invalid
                    const char* error_msg = "Hash not found!";
                    simpleserial_put('r', strlen(error_msg), (uint8_t*)error_msg);

                    // Terminate the program
                    exit(EXIT_FAILURE);  // Stops the program
                }

                // If the hash is valid, continue the program
                // simpleserial_put('r', outlen, digest);
            #endif

    }

    else {
        uint8_t plaintext[16] = "Hello, I am unknown!";  // Exactly 16 bytes
        simpleserial_put('r', 16, plaintext);
    }

}

uint8_t get_pt(uint8_t* pt, uint8_t len)
{
	/**********************************
	* Start user-specific code here. */

    uint16_t start_cycles, stop_cycles, total_cycles;
    TCC0.CTRLA = TC_CLKSEL_DIV1_gc;  // Use system clock without prescaler
    TCC0.CNT = 0;  // Reset counter

    start_cycles = TCC0.CNT;  // Start time measurement

	trigger_high();

    uint8_t* processed_data = process_byte_array(pt, len);  // Process the byte array

	trigger_low();

    TCC0.CTRLA = TC_CLKSEL_OFF_gc;  // Stop the timer
    stop_cycles = TCC0.CNT;  // End time measurement

    total_cycles = (stop_cycles - start_cycles) / 16;  // Calculate the total cycles and divide by 16
    uint8_t cycles_array[16] = {0};  // Create an empty 16-byte array
    memcpy(cycles_array, &total_cycles, sizeof(total_cycles));  // Copy total_cycles to cycles_array

    // Send the total cycles back to the host (2 bytes as uint16_t)
    simpleserial_put('r', sizeof(cycles_array), cycles_array);
	/* End user-specific code here. *
	********************************/
	// simpleserial_put('r', 16, processed_data);
	return 0x00;
}

uint8_t echo_plaintext(uint8_t* data, uint8_t len) {
    // Print received plaintext to the serial monitor
    for (uint8_t i = 0; i < len; i++) {
        putch(data[i]);  // Print each character via UART
    }
    putch('\n');  // Add newline for readability

    // Send the received plaintext back to ChipWhisperer
    simpleserial_put('r', 16, data);  // 'r' indicates a response packet

    return 0x00;  // Indicate success
}


uint8_t clock_cycles(uint8_t* data, uint8_t len)
{
    // Debugging
        // uint8_t plaintext[16] = "Inside! Clock cycles";  // Exactly 16 bytes
        // simpleserial_put('r', 16, plaintext);

    uint16_t start_cycles, stop_cycles, total_cycles;
    TCC0.CTRLA = TC_CLKSEL_DIV1_gc;  // Use system clock without prescaler
    TCC0.CNT = 0;  // Reset counter

    start_cycles = TCC0.CNT;  // Start time measurement
    
    uint8_t* processed_data = process_byte_array(data, len);  // Process the byte array

    TCC0.CTRLA = TC_CLKSEL_OFF_gc;  // Stop the timer
    stop_cycles = TCC0.CNT;  // End time measurement

    total_cycles = stop_cycles - start_cycles;  // Calculate the total cycles
    uint8_t cycles_array[16] = {0};  // Create an empty 16-byte array
    memcpy(cycles_array, &total_cycles, sizeof(total_cycles));  // Copy total_cycles to cycles_array

    // Send the total cycles back to the host (2 bytes as uint16_t)
    simpleserial_put('r', sizeof(cycles_array), cycles_array);
    return 0x00;  // Success
}


uint8_t get_key(uint8_t* k, uint8_t len)
{
    // Load key here
    return 0x00;
}

uint8_t reset(uint8_t* x, uint8_t len)
{
    // Reset state here if needed
    return 0x00;
}

#if SS_VER == SS_VER_2_1
uint8_t aes(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
    uint8_t req_len = 0;
    uint8_t err = 0;

    if (scmd & 0x02) {
        req_len += 16;
        if (req_len > len) {
            return SS_ERR_LEN;
        }
        err = get_key(buf + req_len - 16, 16);
        if (err)
            return err;
    }
    if (scmd & 0x01) {
        req_len += 16;
        if (req_len > len) {
            return SS_ERR_LEN;
        }
        err = get_pt(buf + req_len - 16, 16);
        if (err)
            return err;
    }

    if (len != req_len) {
        return SS_ERR_LEN;
    }

    return 0x00;

}
#endif

int main(void)
{
    platform_init();
    init_uart();
    trigger_setup();

    // Startup message for debugging
    putch('T'); putch('a'); putch('r'); putch('g'); putch('e'); putch('t');
    putch(' ');
    putch('R'); putch('e'); putch('a'); putch('d'); putch('y');
    putch('\n');

    simpleserial_init();

    // Register SimpleSerial commands
    simpleserial_addcmd('p', 16, get_pt);      // Process plaintext
    simpleserial_addcmd('m', 16, clock_cycles);
    simpleserial_addcmd('k', 16, get_key);    // Load key
    simpleserial_addcmd('x', 0, reset);       // Reset state
    simpleserial_addcmd('e', 0, echo_plaintext);

    while (1) {

        simpleserial_get();  // Process incoming commands
    }
}

