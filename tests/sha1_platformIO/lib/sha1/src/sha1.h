// Written by Simone Albano on 20/02/2023

#ifndef SHA1_H_
#define SHA1_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define buffer_64bit 8 // 8*64 = 512 bit
#define buffer_words 16 // 32*16 = 512 bits
#define buffer_bytes 64 // 8*64 = 512 bits
#define max_padding_block_len 56 // If greater -> new padding block

#define a2e_len 5 // sha1 working variable vector length
#define H_len 5 // hash vector length in words
#define W_len 80 // sha1 schedule vector length in words

#define sha1_cycles 79

#define K0 0x5a827999 // From 0 to 19
#define K1 0x6ed9eba1 // From 20 to 39
#define K2 0x8f1bbcdc // From 40 to 59
#define K3 0xca62c1d6 // From 60 to 79

#define H0 0x67452301
#define H1 0xEFCDAB89
#define H2 0x98BADCFE
#define H3 0x10325476
#define H4 0xC3D2E1F0

// Struct & Unions

union W_vector {
    // uint32/8_t vector used in sha1 schedule
    uint32_t W32[W_len];
    uint8_t W8[W_len*sizeof(uint32_t)];
};

union padding_buffer_vector {
    uint8_t PAD8[buffer_bytes];
    uint64_t PAD64[buffer_64bit];
};

typedef struct sha1 {
    bool chunk_ovf_flag; // Set if last chunk length > 56 bytes
    // uint8_t P8[buffer_bytes]; 64 uint8_t vector used to store the padding sequence
    union padding_buffer_vector padding_buffer;
    //uint32_t W[W_len]; 80 uint32_t vector used in sha1 schedule
    union W_vector W;
    uint64_t message_len;
    uint32_t H[H_len]; // H constants vector
    uint32_t a2e[a2e_len]; // sha1 working variables
    uint32_t T; // sha1 temp variable
} sha1;

// Public Prototypes
/* Not used any more, now all arrays are static
bool sha1_init(sha1*);
void sha1_free(sha1*);
*/
uint32_t* sha1_compute(sha1*, uint8_t*, uint64_t);

//Macros
// f(x, y, z, t) -----------------------------------------------
#define ch(x, y, z) ((x&y)^((~x)&z)) // From 0 to 19
#define parity(x, y, z) (x^y^z) // From 20 to 39, from 60 to 79
#define maj(x, y, z) ((x&y)^(x&z)^(y&z)) // From 40 to 59
// f(x, y, z, t) -----------------------------------------------
//#define sum(x, y) (((uint32_t)x + (uint32_t)y)%modulo)
//#define modulo 4294967296 // Used for sum mod 2^32
#define ROTL(value, bits) ((value << bits) | ((value >> (32 - bits)))) // Circular rotate left
#define to_big_endian(value) (((value & 0xff) << 24) | ((value & 0xff00) << 8) | ((value & 0xff0000) >> 8) | ((value & 0xff000000) >> 24))

#ifdef __cplusplus
}
#endif
#endif
