/*
Computed Hash: (with -Os flag)
RAM:   [          ]   3.5% (used 286 bytes from 8192 bytes)
Flash: [          ]   2.3% (used 5798 bytes from 253952 bytes)
84983E441C3BD26EBAAE4AA1F95129E5E54670F1
119.77 H/s, in 0.834912 s

Computed Hash: (with -O3 flag)
RAM:   [          ]   3.5% (used 286 bytes from 8192 bytes)
Flash: [          ]   4.4% (used 11200 bytes from 253952 bytes)
84983E441C3BD26EBAAE4AA1F95129E5E54670F1
121.49 H/s, in 0.823128 s
*/

#include <Arduino.h>
#include <sha1.h>

void setup() {
Serial.begin(115200);

  sha1 hash;
  uint8_t message[57] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
  uint32_t* result;
  int iterations = 100;
  double tic, toc;

  tic = micros();
  for(int i = 0; i < iterations; i++) {
    result = sha1_compute(&hash, message, sizeof(message)-1);
  }
  toc = micros();

  Serial.println("\nComputed Hash:");
  for(int i = 0; i < 5; i++) {
    Serial.print(result[i], HEX);
  }
  Serial.print("\n");
  Serial.print(iterations/((toc-tic)/1E6));
  Serial.print(" H/s, in ");
  Serial.print((toc-tic)/1E6, 6);
  Serial.print(" s");
}

void loop() {
}