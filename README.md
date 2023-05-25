# HMAC-SHA1-TOTP
HMAC-SHA1-TOTP Auth Algorithm for Embedded Devices
 
Implementation of the TOTP authentication algorithm written in C, suitable for Embedded application or other enviroments where a low memory impact is required.
The current version of the algorithm is based on the HMAC-sha1 hash-based message authentication code, but future versions can be implemented using other hash functions like SHA256 and SHA512.

### Library usage
```c
TOTP totp; // Initialize the structure
uint32_t result = totp_compute(TOTP* totp, uint8_t* key, uint32_t key_length, uint32_t epoch, uint32_t t0, uint32_t t_interval, uint8_t digit);
```
```
where:
- TOTP* totp is a pointer to the struct
- key is the secret key in ASCII (not base32) used to perform the TOTP computation
- key_length is the actual bit length of the key (excluding the NULL char at the end)
- epoch is the unix-epoch in seconds (seconds passed from 01/01/1970,00:00)
- t0 is a time factor (the use is described in the implementation, default = 00)
```
### TOTP performances on ATMega2560 @ 16MHz clock
```
Performances with build_flags = -Os:
iterations = 100
RAM:   [          ]   4.1% (used 332 bytes from 8192 bytes)
Flash: [          ]   3.5% (used 8818 bytes from 253952 bytes)
Computed TOTP with epoch = 00000001, key = "12345678901234567890", digit = 6: 755224
TOTP per second: 59.22
Execution time for 1 TOTP computation: 0.016885s

Performances with build_flags = -O3:
iterations = 100
RAM:   [          ]   4.1% (used 332 bytes from 8192 bytes)    
Flash: [=         ]  10.1% (used 25634 bytes from 253952 bytes)
Computed TOTP with epoch = 00000001, key = "12345678901234567890", digit = 6: 755224
TOTP per second: 61.69
Execution time for 1 TOTP computation: 0.016209s
```
### SHA1 performances on ATMega2560 @ 16MHz clock
```
Test vector: uint8_t message[56] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
Iteration: 100

Computed Hash: (with -Os flag)
RAM:   [=         ]   3.5% (used 286 bytes from 8192 bytes)
Flash: [=         ]   2.3% (used 5798 bytes from 253952 bytes)
hash: 84983E441C3BD26EBAAE4AA1F95129E5E54670F1
119.77 H/s, in 0.834912 s

Computed Hash: (with -O3 flag)
RAM:   [         ]   3.5% (used 286 bytes from 8192 bytes)
Flash: [         ]   4.4% (used 11200 bytes from 253952 bytes)
hash: 84983E441C3BD26EBAAE4AA1F95129E5E54670F1
121.49 H/s, in 0.823128 s
```
### Compile the code
Compiling instruction for Windows:
```bash
cd ~tests\tests_windows\

sha1test.c:
    gcc -O3 sha1test.c ../../lib/sha1.c -o sha1test.exe
HMACsha1test.c:
    gcc -O3 HMACsha1test.c ../../lib/HMACsha1.c ../../lib/sha1.c -o HMACsha1test.exe
totptest.c:
    gcc -O3 totptest.c ../../lib/totp.c ../../lib/HMACsha1.c ../../lib/sha1.c -o totptest.exe
```
