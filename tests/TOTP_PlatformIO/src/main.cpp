/*
Performances with build_flags = -Os:
    iterations = 100
    RAM:   [          ]   4.1% (used 332 bytes from 8192 bytes)
    Flash: [          ]   3.5% (used 8818 bytes from 253952 bytes)
    Computed TOTP with epoch = 00000001, key = "12345678901234567890", digit = 6: 755224
    TOTP per second: 59.22
    Execution time for 1 TOTP computation: 0.016885s
    iterations = 100
Performances with build_flags = -O3:
    RAM:   [          ]   4.1% (used 332 bytes from 8192 bytes)    
    Flash: [=         ]  10.1% (used 25634 bytes from 253952 bytes)
    Computed TOTP with epoch = 00000001, key = "12345678901234567890", digit = 6: 755224
    TOTP per second: 61.69
    Execution time for 1 TOTP computation: 0.016209s
*/

#include <Arduino.h>
#include <totp.h>

void setup() {
    Serial.begin(115200);
    uint8_t iterations = 100;

    TOTP totp;
    uint8_t key[21] = "12345678901234567890";
    uint32_t epoch = iterations;
    double tic, toc;
    uint32_t result;
    
    tic = micros();
    for(uint8_t i = iterations; i > 0; i--) {
        result = totp_compute(&totp, key, sizeof(key)-1, epoch, 0, 30, 6);
        epoch--;
    }
    toc = micros();

    Serial.print("Computed TOTP with epoch = 1, digit = 6: ");
    Serial.println(result);
    Serial.print("TOTP per second: ");
    Serial.println(iterations/((toc-tic)/1E6));
    Serial.print("Execution time for 1 TOTP computation: ");
    Serial.print(((toc-tic)/1E6)/iterations, 6);
    Serial.print("s");
}

void loop() {
}
