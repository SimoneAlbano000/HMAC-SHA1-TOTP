// Written by Simone Albano on 30/04/2023

#ifndef HMACSHA1_H_
#define HMACSHA1_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sha1.h"

#define sha1_block_size 64
#define sha1_hash_len 20
#define sha1_hash_len_word 5

#define K_opad 0x5c
#define K_ipad 0x36

// Struct
typedef struct HMAC_sha1 {
    sha1 hash;
    uint8_t key[sha1_block_size];
    uint64_t key_len;
    uint64_t message_len;
    uint8_t opad[sha1_block_size];
    uint8_t ipad[sha1_block_size];
    uint8_t* hash_arg;
    uint8_t* endptr;
} HMAC_sha1;

//Public Prototypes
/* Not used anymore, all array are static
bool HMAC_sha1_init(HMAC_sha1*);
void HMAC_sha1_free(HMAC_sha1*);
*/
uint32_t* HMAC_sha1_compute(HMAC_sha1*, uint8_t*, uint64_t, uint8_t*, uint64_t);

#ifdef __cplusplus
}
#endif
#endif
