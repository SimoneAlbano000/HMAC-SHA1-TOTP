// Dell Latitude 7490: 1.124MH/s

#include <stdio.h>
#include <string.h>
#include "../../lib/sha1.h"

int main() {
    sha1 hash;

    uint8_t* message[12] = {
    "",
    "a",
    "N8xfoY2XWZ37B3KUhX3o",
    "TP68gG8BQfmgVZkDWibv6tr4v2JKOkSV",
    "j54pGBaOksrTdRA41OymX6iUQmyuZ3yPdZyFSzAWbUmLMepYUEAY2G3",
    "DaJqRQBnkLcS2iDbunFHqaDBCKakTu1cNEqaO9NeygvJcpHF4L1lJo7h",
    "kjYJ2DuZ74rzqFjPzu9EseeqK1EwzZFdKTkYHojTKP8vW4is4vSqOihQ9",
    "ySqrw3nWCdKPuTyBmERxQTDzDdJqMUgi3rhYDbsau6E3473QxqlbRkFepJdn6nD",
    "1Ep2Ruts6lyLO8x09ddkzmbBeM40C3Lja5leK3lyV35GU4ajE7bW8NNwxGhy82nd",
    "ImG2VtjxUehPoDwXyPbNmqiSMxkOCrbAaxSaExlX7V4VvvHw8C79lMmrUgP79Hxek",
    "DhR8csgpjJQ9ag9OH6qDrWzeaO1Fmn7CvMiKO67pcN2uPOQMziOXdqDHiLgT3bjcrMRJuccP16I9WUCACmMOaN8iGeQsz4ieQpo7o0XEUsDx5tFvttA9coUL",
    "OG5aHEikPH7ajRRIEts3Cf7B8NTsVr1i9j2pk4qnQSLKCHibTuM850ITWPrf2RXFgQaffZUs9GWPV1War7pHaCltrUTLwkkqRGc2d3FJwHJejqNxsywiLCOED1thteA4gOWSYO2hbmb3LHj1UEMMs92XkEvJ8netKFkGIbVipNo7Rv0ge6WHTq4rRdmCkPRvN6Il89MVzlNkAVbRsAKxdA68dnTdLgxrl59R8sEVzycIAeC628x4REXSghLVOAGKKtllKSQMDHdV7KDquuJD9ETTccDLlQpbLJxDTCN9HSnQs0Ql2ANstXHTPgKI7HYPL81TRJmkHmFAUSGaoSfPyugws4zhGv0vcgrA7VE1CZFLfDFWYCOPJuZrrTj9PLwx10Q3g5NjhkMxwB53zBITnlsa64wMMNZS41hAzAjev5dYeTRqvdqpjMUtTGEej3bH27Vw4nGh1ViJv3T9cgBvgGsA0uo8FCQI9fv96n5f5IYNtNaKt3ngaJlCjpcnlURE"
    };

    uint8_t* digest[12] = {
    "da39a3ee5e6b4b0d3255bfef95601890afd80709",
    "86f7e437faa5a7fce15d1ddcb9eaeaea377667b8",
    "57eba3d93019798515685dcd93c13c7a673cea49",
    "afcea39d73f494cc62ced071a91d519108ede3c8",
    "52139a685214f949dc6bcc121c24333c94f2bce9",
    "5384f04bf5bab0b80899b627a709a2bb2551ce25",
    "b0b30f85a8c952b516b025e7440d2edb0713a245",
    "f54aa5de0d2eb40e38d8fe2a260e1798f4bea516",
    "76e7f03b15f0c6c8421853f09b882ecf9aef7678",
    "5e79ad4b58e38cb958e3d91f1ca3aeb911d64205",
    "1530c69e0252bbd023243656d21f5c3c287aaa1c",
    "a533723a2dfc6935a8d80b9ccaceeaf8dda38f1d"
    };

    uint32_t* result;

    for(int i = 0; i < 12; i++) {
        result = sha1_compute(&hash, message[i], strlen(message[i]));
        printf("\nComputed hash:\n");
        for(int j = 0; j < 5; j++) {
            printf("%0x", result[j]);   
        }
        printf("\nExpected output:\n");
        printf("%s\n", digest[i]);
    }
}