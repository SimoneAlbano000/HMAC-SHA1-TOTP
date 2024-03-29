// Written by Simone Albano on 24/05/2023

#include "totp.h"

void totp_compute(TOTP* totp, uint8_t* key, uint32_t key_length, uint32_t unix_epoch, uint32_t t0, uint32_t t_interval, uint8_t digit, uint8_t* destination) {
    // Calculate the epoch block and fill the epoch vector
    uint32_t epoch_counter = (uint32_t)floor(((double)unix_epoch-t0)/t_interval);
    totp->unix_epoch_counter_str[0] = 0x00;
    totp->unix_epoch_counter_str[1] = 0x00;
    totp->unix_epoch_counter_str[2] = 0x00;
    totp->unix_epoch_counter_str[3] = 0x00;
    totp->unix_epoch_counter_str[4] = (uint8_t)((epoch_counter >> 24) & 0xff);
    totp->unix_epoch_counter_str[5] = (uint8_t)((epoch_counter >> 16) & 0xff);
    totp->unix_epoch_counter_str[6] = (uint8_t)((epoch_counter >> 8) & 0Xff);
    totp->unix_epoch_counter_str[7] = (uint8_t)((epoch_counter & 0Xff));
    // Compute the HMAC-sha1 and copy the result into a separate vector
    memcpy(totp->HMAC_digest.HMAC32, HMAC_sha1_compute(&totp->HMAC, totp->unix_epoch_counter_str, epoch_str_len, key, key_length), sizeof(uint32_t)*digest_len_word);
    // Extract the LSB of the (uint8_t)HMAC[19] vector
    totp->LSB19 = totp->HMAC_digest.HMAC32[4] & 0xf;
    // HMAC -> to big endian
    for(uint8_t i = 0; i < digest_len_word; i++) {
        totp->HMAC_digest.HMAC32[i] = to_big_endian(totp->HMAC_digest.HMAC32[i]);
    }
    // Copy the 4 bytes from address LSB19 discarting the MSB of bin_code[LSB19+0] to avoid sign confusion
    memcpy(totp->bin_code_str, (totp->HMAC_digest.HMAC8)+(totp->LSB19), sizeof(uint32_t));
    totp->bin_code_str[0] &= 0x7f;
    // Compute the final totp value
    totp->bin_code = str2uint32_t(totp->bin_code_str);
    totp->bin_code %= (uint32_t)pow(10, digit);

    // Convert the totp numerical value to string and copy result into destination string ---
    // Allocate memory for the final totp string
    totp->totp_str = (uint8_t*)malloc(sizeof(uint8_t)*(digit + 1));
    sprintf(totp->totp_str, "%lu", totp->bin_code);
    uint8_t num_len = strlen(totp->totp_str);
    if(num_len != digit) {
        for(uint8_t i = 0; i <= num_len ; i++) {
            // Shift the whole string i times to the rigth and insert i zeros
            totp->totp_str[digit - i] = totp->totp_str[num_len - i];
        }
        // Add the necessary padding zeros in front of the totp string
        memset(totp->totp_str, '0', sizeof(uint8_t)*(digit - num_len));
    }
    // Copy the result into the destination string
    strcpy(destination, totp->totp_str);
    free(totp->totp_str);
    // --------------------------------------------------------------------------------------
    return;
}
