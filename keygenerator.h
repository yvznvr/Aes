#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <stdint.h>
#include "tables.h"

typedef unsigned char BYTE;

class KeyGenerator
{
public:
    KeyGenerator();
    KeyGenerator(uint8_t* key, int keySize);
    ~KeyGenerator();
    uint8_t* getKey(int roundNumber);
    bool setKey(uint8_t* key, int keySize);
    bool calcKeys();
private:
    uint8_t* key;
    uint8_t* extendedKey;
    int keySize;
    BYTE *sbox, *rcon;
};

#endif // KEYGENERATOR_H
