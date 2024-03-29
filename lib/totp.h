// Written by Simone Albano on 24/05/2023

#ifndef TOTP_H_
#define TOTP_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <math.h>
#include <stdio.h>
#include "HMACsha1.h"

#define to_big_endian(value) (((value & 0xff) << 24) | ((value & 0xff00) << 8) | ((value & 0xff0000) >> 8) | ((value & 0xff000000) >> 24))
#define str2uint32_t(str) (((uint32_t)str[0] << 24) | ((uint32_t)str[1] << 16) | ((uint32_t)str[2] << 8) | (uint32_t)str[3])

#define digest_len_byte 20
#define digest_len_word 5
#define epoch_str_len 8
#define bin_code_len 4

// Unions and Structs
union HMAC_digest_union {
    uint32_t HMAC32[digest_len_word];
    uint8_t HMAC8[digest_len_byte];
};

typedef struct TOTP {
    HMAC_sha1 HMAC;
    union HMAC_digest_union HMAC_digest;
    uint8_t LSB19:4;
    uint8_t unix_epoch_counter_str[epoch_str_len];
    uint8_t bin_code_str[bin_code_len]; 
    uint32_t bin_code;
    uint8_t* totp_str;
} TOTP;

// Public Prototypes
void totp_compute(TOTP* , uint8_t* , uint32_t , uint32_t , uint32_t, uint32_t, uint8_t, uint8_t*);

#ifdef __cplusplus
}
#endif
#endif