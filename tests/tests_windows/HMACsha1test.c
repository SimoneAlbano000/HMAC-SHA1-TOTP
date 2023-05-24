// hmac-sha1: de7c9b85b8b78aa6bc8a7a36f70a90701c9db4d9

#include <stdio.h>
#include "../../lib/HMACsha1.h"

int main() {

    HMAC_sha1 HMAC; // Init the HMAC_sha1 struct
    char key[3] = "key";
    char message[43] = "The quick brown fox jumps over the lazy dog";
    uint32_t* result = HMAC_sha1_compute(&HMAC, message, sizeof(message), key, sizeof(key));
     for(int i = 0; i < 5; i++) {
        printf("%0x", result[i]);
    }

    return 0;
}
