

nonce 4098331810 taucht ab 0x35 bis 0x4a auf
nonce 0xf44794a2        11110100 01000111 10010100 10100010 //ist nur in 0x35 bis 4a
version 0x20386000      00100000 00111000 01100000 00000000

mask                    11111111 11111111

address 0x34            00110100 rev 00101100
address 0x35            00110101 rev 10101100
address 0x4a            01001010 rev 01010010
address 0x4b            01001011 rev 11010010

nonce 0xdc9d7bb8        11011100 10011101 01111011 10111000 //ist in 0x34 und 0x35
version 0x20f28000      00100000 11110010 10000000 00000000

cchatgpt:
Die nonce 0xf44794a2 taucht ab 0x35 bis 0x4a auf.
Die nonce 0xdc9d7bb8 taucht in 0x34 jedoch nicht in 0x35 auf. Gibt es eine systemation auf bit ebene?


                                                                         mask   10101000 00111000
I (205394) test_bm1366: chip address: 0x13 (19)   00010011
I (207404) test_bm1366: Result[1]: Nonce 1195255666                0x473e2772   01000111 00111110 00100111 01110010
                                                    rolled-version 0x31ca4000   00110001 11001010 01000000 00000000
I (207574) test_bm1366: Result[2]: Nonce 2856921458                0xaa492972   10101010 01001001 00101001 01110010
                                                    rolled-version 0x3355e000   00110011 01010101 11100000 00000000

I (210984) test_bm1366: chip address: 0x14 (20)   00010100
I (211364) test_bm1366: Result[1]: Nonce 2529831618 (0x96ca2ac2) rolled-version 0x23286000   00100011 00101000 01100000 00000000
I (213174) test_bm1366: Result[2]: Nonce 2856921458 (0xaa492972) rolled-version 0x3355e000   00110011 01010101 11100000 00000000
