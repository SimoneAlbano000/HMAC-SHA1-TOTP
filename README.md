# HMAC-SHA1-TOTP
 HMAC-SHA1-TOTP Auth Algorithm for Embedded Devices
 
 Implementation of the TOTP authentication algorithm written in C, suitable for Embedded application or other enviroments where a low memory impact is required.
 The current version of the algorithm is based on the HMAC-sha1 hash-based message authentication code, but future versions can be implemented using other hash functions like SHA256 and SHA512.

### Performances on ATMega2560 @ 16MHz clock
```
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
```
