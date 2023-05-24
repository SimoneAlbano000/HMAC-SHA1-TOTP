// Written by Simone Albano on 30/04/2023

#include "HMACsha1.h"

// Private Prototypes
static void HMAC_sha1_pad_key(HMAC_sha1*, uint8_t*);
static void compute_opad_ipad(HMAC_sha1*);

static void HMAC_sha1_pad_key(HMAC_sha1* HMAC, uint8_t* key) {
    // Padding the message (memset used for clearing the key array)
    memset(HMAC->key, 0, sizeof(uint8_t)*sha1_block_size);
    if(HMAC->key_len > sha1_block_size) {
        sha1_compute(&HMAC->hash, key, HMAC->key_len);
        memcpy(HMAC->key, HMAC->hash.H, sizeof(uint32_t)*sha1_hash_len_word);
    } else {
        memcpy(HMAC->key, key, sizeof(uint8_t)*HMAC->key_len);
    }
    return;
}

static void compute_opad_ipad(HMAC_sha1* HMAC) {
    // Compute opad and ipad
    for(uint8_t i = 0; i < sha1_block_size; i++) {
        HMAC->opad[i] = HMAC->key[i] ^ K_opad;
        HMAC->ipad[i] = HMAC->key[i] ^ K_ipad;
    }
    return;
}

uint32_t* HMAC_sha1_compute(HMAC_sha1* HMAC, uint8_t* message, uint64_t message_length, uint8_t* key0, uint64_t key_length) {
    HMAC->key_len = key_length;
    HMAC->message_len = message_length;
    //Pad the key
    HMAC_sha1_pad_key(HMAC, key0);
    // Compute the values of opad and ipad
    compute_opad_ipad(HMAC);
    // First sha1 round
    HMAC->hash_arg = (uint8_t*)malloc(sizeof(uint8_t)*(sha1_block_size+HMAC->message_len));
    HMAC->endptr = mempcpy(HMAC->hash_arg, HMAC->ipad, sizeof(uint8_t)*sha1_block_size);
    memcpy(HMAC->endptr, message, HMAC->message_len);
    sha1_compute(&HMAC->hash, HMAC->hash_arg, sha1_block_size+HMAC->message_len);
    // Second sha1 round (also realloc hash_arg array memory size in order to obtain the length (sha1_block_size+sha1_hash_len))
    HMAC->hash_arg = (uint8_t*)realloc(HMAC->hash_arg, sizeof(uint8_t)*(sha1_block_size+sha1_hash_len));
    HMAC->endptr = mempcpy(HMAC->hash_arg, HMAC->opad, sizeof(uint8_t)*sha1_block_size);
    for(uint8_t i = 0; i < H_len; i++) {
        *(((uint32_t*)HMAC->endptr)+i) = to_big_endian(HMAC->hash.H[i]);
    }
    sha1_compute(&HMAC->hash, HMAC->hash_arg, sha1_block_size+sha1_hash_len);
    // Free all the allocated memory
    free(HMAC->hash_arg);
    return HMAC->hash.H;
}

/* Not used anymore, all array are static
bool HMAC_sha1_init(HMAC_sha1* HMAC) {
    // Allocate memory for the HMAC struct variables
    HMAC->key = (uint8_t*)calloc(sha1_block_size, sizeof(uint8_t));
    // Check for memory allocation errors
    if(HMAC->key==NULL) {
        return false;
    }
    return true;
}

void HMAC_sha1_free(HMAC_sha1* HMAC) {
    // Free all the allocated memory
    free(HMAC->hash_arg);
    free(HMAC->key);
    return;
}
*/
