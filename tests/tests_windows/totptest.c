#include <stdio.h>
#include <time.h>
#include "../../lib/totp.h"

int main() {

    TOTP totp;
    uint8_t key[20] = "12345678901234567890";
    while(1) {
        uint32_t epoch = (double)time(NULL);
        uint32_t result = totp_compute(&totp, key, sizeof(key), epoch, 0, 30, 6);
        printf("%d\n", result);
    }
    return 0;
}
