# HMAC-SHA1-TOTP
 HMAC-SHA1-TOTP Auth Algorithm for Embedded Devices
 
 Implementation of the TOTP authentication algorithm written in C, suitable for Embedded application or other enviroments where a low memory impact is required.
 The current version of the algorithm is based on the HMAC-sha1 hash-based message authentication code, but future versions can be implemented using other hash functions like SHA256 and SHA512.

### SHA1 performances on ATMega2560 @ 16MHz clock
```
Test vector: uint8_t message[56] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
Iteration: 100

Computed Hash: (with -Os flag)
RAM:   [-         ]   3.5% (used 286 bytes from 8192 bytes)
Flash: [-         ]   2.3% (used 5798 bytes from 253952 bytes)
hash: 84983E441C3BD26EBAAE4AA1F95129E5E54670F1
119.77 H/s, in 0.834912 s

Computed Hash: (with -O3 flag)
RAM:   [-         ]   3.5% (used 286 bytes from 8192 bytes)
Flash: [-         ]   4.4% (used 11200 bytes from 253952 bytes)
hash: 84983E441C3BD26EBAAE4AA1F95129E5E54670F1
121.49 H/s, in 0.823128 s
```
### SHA1 performances on Dell Latitude 7490: 
- i5-8350U @ 1.9GHz with 8Gb of ram: 1.124MH/s (with -O3 optimization flag)

### Compile the code
Compiling instruction for Windows:
```
cd ~tests\tests_windows\

sha1test.c:
    gcc -O3 sha1test.c ../../lib/sha1.c -o sha1test.exe
HMACsha1test.c:
    gcc -O3 HMACsha1test.c ../../lib/HMACsha1.c ../../lib/sha1.c -o HMACsha1test.exe
totptest.c:
    gcc -O3 totptest.c ../../lib/totp.c ../../lib/HMACsha1.c ../../lib/sha1.c -o totptest.exe
```
