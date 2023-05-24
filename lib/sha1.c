// Written by Simone Albano on 20/02/2023

#include "sha1.h"

// Private Prototypes
static void padding(sha1*, uint8_t*);
static void fill_W(sha1*, uint8_t*, uint8_t, bool pad);
static void compute_round(sha1*);
static void update_H(sha1*);

static void padding(sha1* hash, uint8_t* message) {
    // Obtain the length of the last block
    uint8_t last_block_len_byte = (hash->message_len)%buffer_bytes;
    if(last_block_len_byte < max_padding_block_len) { // No new block needed
        // Copy last message block into the padding buffer (memset clear the entire array)
        memset(hash->padding_buffer.PAD8, 0, sizeof(uint8_t)*buffer_bytes);
        // If the message is multiple of 64 bytes, 64%64=0, and memcpy actually do not perform any operations
        memcpy(hash->padding_buffer.PAD8, message+((hash->message_len)-last_block_len_byte), sizeof(uint8_t)*last_block_len_byte); 
        // Append the value 0x80 (int 128)
        hash->padding_buffer.PAD8[last_block_len_byte] = 0x80;
        // Add the message length in bits (for which the last 64 bits are reserved)
        hash->padding_buffer.PAD64[buffer_64bit-1] = to_big_endian(((hash->message_len)*8))<<32;
        hash->chunk_ovf_flag = false;
    } else {
        // Now the constant 0x80 needs to be added in the block before the padding one (will be done in the main loop function), (memset clear the entire array)
        memset(hash->padding_buffer.PAD8, 0, sizeof(uint8_t)*buffer_bytes);
        hash->padding_buffer.PAD64[buffer_64bit-1] = to_big_endian(((hash->message_len)*8))<<32;
        hash->chunk_ovf_flag = true;
    }
    return;
}

static void fill_W(sha1* hash, uint8_t* message_chunk, uint8_t chunk_length, bool pad) {
    // Fill the vector as described in the nist sha1 documentation (add 0x80 padding if necessary)
    // for 0 <= t < 16
    if(pad == true) {
        memset(hash->W.W8, 0, sizeof(uint8_t)*buffer_bytes);
        memcpy(hash->W.W8, message_chunk, sizeof(uint8_t)*chunk_length);
        hash->W.W8[chunk_length] = 0x80;
        for(uint8_t t = 0; t < buffer_words; t++) {
            hash->W.W32[t] = to_big_endian(hash->W.W32[t]);
        }
    } else {
        memcpy(hash->W.W8, message_chunk, sizeof(uint8_t)*chunk_length);
        for(uint8_t t = 0; t < buffer_words; t++) {
            hash->W.W32[t] = to_big_endian(hash->W.W32[t]);
        }
    }
    // for 16 <= t < 80
    for(uint8_t t = buffer_words; t < W_len; t++) {
        hash->W.W32[t] = ROTL(((hash->W.W32[t-3])^(hash->W.W32[t-8])^(hash->W.W32[t-14])^(hash->W.W32[t-16])), 1);
    }
    return;
}

static void compute_round(sha1* hash) {
    // Main sha1 loop
    for(uint8_t t = 0; t <= sha1_cycles; t++) {
        if(t <= 19) {
           hash->T = ROTL(hash->a2e[0], 5) + ch(hash->a2e[1], hash->a2e[2], hash->a2e[3]) + hash->a2e[4] + K0 + hash->W.W32[t];
           hash->a2e[4] = hash->a2e[3];
           hash->a2e[3] = hash->a2e[2];
           hash->a2e[2] = ROTL(hash->a2e[1], 30);
           hash->a2e[1] = hash->a2e[0];
           hash->a2e[0] = hash->T;
        } else if(t > 19 && t <= 39) {
           hash->T = ROTL(hash->a2e[0], 5) + parity(hash->a2e[1], hash->a2e[2], hash->a2e[3]) + hash->a2e[4] + K1 + hash->W.W32[t];
           hash->a2e[4] = hash->a2e[3];
           hash->a2e[3] = hash->a2e[2];
           hash->a2e[2] = ROTL(hash->a2e[1], 30);
           hash->a2e[1] = hash->a2e[0];
           hash->a2e[0] = hash->T;
        } else if(t > 39 && t <= 59) {
           hash->T = ROTL(hash->a2e[0], 5) + maj(hash->a2e[1], hash->a2e[2], hash->a2e[3]) + hash->a2e[4] + K2 + hash->W.W32[t];
           hash->a2e[4] = hash->a2e[3];
           hash->a2e[3] = hash->a2e[2];
           hash->a2e[2] = ROTL(hash->a2e[1], 30);
           hash->a2e[1] = hash->a2e[0];
           hash->a2e[0] = hash->T;
        } else if(t > 59 && t <= 79) {
           hash->T = ROTL(hash->a2e[0], 5) + parity(hash->a2e[1], hash->a2e[2], hash->a2e[3]) + hash->a2e[4] + K3 + hash->W.W32[t];
           hash->a2e[4] = hash->a2e[3];
           hash->a2e[3] = hash->a2e[2];
           hash->a2e[2] = ROTL(hash->a2e[1], 30);
           hash->a2e[1] = hash->a2e[0];
           hash->a2e[0] = hash->T;
        }
    }  
    return;      
}

static void update_H(sha1* hash) {
    // Update sha1 H[] hash vector
    hash->H[0] += hash->a2e[0];
    hash->H[1] += hash->a2e[1];
    hash->H[2] += hash->a2e[2];
    hash->H[3] += hash->a2e[3];
    hash->H[4] += hash->a2e[4];
    return;
}

uint32_t* sha1_compute(sha1* hash, uint8_t* message, uint64_t message_length) {
    // Clear the struct (in the case this is not the first hash)
    hash->H[0] = H0;
    hash->H[1] = H1;
    hash->H[2] = H2;
    hash->H[3] = H3;
    hash->H[4] = H4;
    // Set the message length and add padding
    hash->message_len = message_length;
    padding(hash, message);
    // Compute the number of cycles to be performed
    uint64_t n_of_cycles = ((message_length+(buffer_bytes-(message_length%buffer_bytes)))/buffer_bytes);
    // Main chunks loop -------------------------------------------------------
    for(uint64_t N = 0; N < (n_of_cycles)-1; N++) {
        // Process the message in 512 bits chunks (message+(buffer_bytes*N))
        // Fill the W schedule vector with the current chunk of the message
        fill_W(hash, message+(buffer_bytes*N), buffer_bytes, false);
        // Update the a2e vector
        memcpy(hash->a2e, hash->H, sizeof(uint32_t)*a2e_len);
        // Compute the sha1 round
        compute_round(hash);
        // Update the H vector
        update_H(hash);
    } 
    // ----------------------------------------------------------------------
    // Process the last two chunks of message
    if(hash->chunk_ovf_flag==false) {
        // Hash the padding buffer
        fill_W(hash, hash->padding_buffer.PAD8, buffer_bytes, false);
        memcpy(hash->a2e, hash->H, sizeof(uint32_t)*a2e_len);
        compute_round(hash);
        update_H(hash);
    } else {
        // Hash the chunk before the padding buffer (where ((hash->message_len)%buffer_bytes) is the length of the processed chunk)
        fill_W(hash, message+(buffer_bytes*(n_of_cycles-1)), ((hash->message_len)%buffer_bytes), true);
        memcpy(hash->a2e, hash->H, sizeof(uint32_t)*a2e_len);
        compute_round(hash);
        update_H(hash);
        // Hash the padding buffer
        fill_W(hash, hash->padding_buffer.PAD8, buffer_bytes, false);
        memcpy(hash->a2e, hash->H, sizeof(uint32_t)*a2e_len);
        compute_round(hash);
        update_H(hash);
    }
    // Return the pointer to the uint32_t H hash vector
    return hash->H;
}

/* Not used any more, now all arrays are static

bool sha1_init(sha1* hash) {
    // Allocate Memory for the padding buffer
    hash->padding_buffer = (uint8_t*)malloc(sizeof(uint8_t)*buffer_bytes);
    // Allocate memory for the W schedule vector
    hash->W = (uint32_t*)malloc(sizeof(uint32_t)*W_len);
    // Allocate Memory for the uint32_t H vector and fill it with the sha1 constants
    hash->H = (uint32_t*)malloc(sizeof(uint32_t)*H_len);
    // Allocate memory for the five sha1 working variables a, b, c, d, e
    hash->a2e = (uint32_t*)malloc(sizeof(uint32_t)*a2e_len);
    // Check for allocation failures
    if ((hash->padding_buffer==NULL)||(hash->H==NULL)||(hash->W==NULL)||(hash->a2e==NULL)) {
        return false;
    } else {
        return true;
    }
}

void sha1_free(sha1* hash) {
    //Free all the allocated memory
    free(hash->padding_buffer);
    free(hash->W);
    free(hash->H);
    free(hash->a2e);
    return;
}
*/
