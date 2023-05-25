#include <Arduino.h>
#include <totp.h>

void setup() {
    Serial.begin(115200);

    TOTP totp;
    uint8_t key[21] = "12345678901234567890";
    uint32_t epoch = 1;
    double tic, toc;
    uint32_t result;

    tic = micros();
    result = totp_compute(&totp, key, sizeof(key)-1, epoch, 0, 30, 6);
    toc = micros();

    Serial.print("Computed TOTP: ");
    Serial.println(result);
    Serial.print("TOTP per second: ");
    Serial.println(1/((toc-tic)/1E6));
    Serial.print("Execution time for 1 TOTP computation: ");
    Serial.print((toc-tic));
    Serial.print(" μs");
}

void loop() {
}
