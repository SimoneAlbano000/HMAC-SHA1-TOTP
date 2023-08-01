/*
Performances with build_flags = -Os:
    iterations = 100
    RAM:   [          ]   4.1% (used 332 bytes from 8192 bytes)
    Flash: [          ]   3.5% (used 8818 bytes from 253952 bytes)
    Computed TOTP with epoch = 00000001, key = "12345678901234567890", digit = 6: 755224
    TOTP per second: 59.22
    Execution time for 1 TOTP computation: 0.016885s
Performances with build_flags = -O3:
    iterations = 100
    RAM:   [          ]   3.6% (used 294 bytes from 8192 bytes)     
    Flash: [=         ]  10.8% (used 27538 bytes from 253952 bytes)
    Computed TOTP with epoch = 00000001, key = "12345678901234567890", digit = 6: 755224
    TOTP per second: 61.69
    Execution time for 1 TOTP computation: 0.016209s
*/

#include <Arduino.h>
#include <totp.h>

void setup() {
    Serial.begin(250000);
    uint32_t iterations = 100;

    TOTP totp;
    uint8_t key[21] = "12345678901234567890";
    uint8_t result[7] = "";
    uint32_t epoch = iterations;
    double tic, toc;
    
    tic = micros();
    for(uint32_t i = iterations; i > 0; i--) {
        totp_compute(&totp, key, sizeof(key)-1, epoch, 0, 30, 6, result);
        epoch--;
        for(uint8_t k = 0; k < 6; k++) {
            Serial.write(result[k]);
        }
        Serial.print("\n");
    }
    toc = micros();

    Serial.print("TOTP per second: ");
    Serial.println(iterations/((toc-tic)/1E6));
    Serial.print("Execution time for 1 TOTP computation: ");
    Serial.print(((toc-tic)/1E6)/iterations, 6);
    Serial.print("s");
}

void loop() { 
}
