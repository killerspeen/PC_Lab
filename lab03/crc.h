//
// fisier crc.h
//
// contine directivele si definitiile utile programelor
// de calcul al codului de control ciclic CRC-CCITT
//

#define CRCCCITT 0x1021
#define MAX_L 100

#include <stdio.h>
#include <stdlib.h>

typedef unsigned short int word;
typedef unsigned char byte;

word calculcrc (word, word, word);
word* tabelcrc (word);
