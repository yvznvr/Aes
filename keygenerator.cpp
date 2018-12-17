#include "keygenerator.h"


KeyGenerator::KeyGenerator()
{
    key = extendedKey = nullptr;
    keySize = 0;
    rcon = Tables::rcon;
    sbox = Tables::sbox;
}

KeyGenerator::KeyGenerator(uint8_t *key, int keySize)
{
    setKey(key, keySize);
    rcon = Tables::rcon;
    sbox = Tables::sbox;
}

KeyGenerator::~KeyGenerator()
{
    delete[] extendedKey;
}

uint8_t *KeyGenerator::getKey(int roundNumber)
{
    return extendedKey + roundNumber * keySize;
}

bool KeyGenerator::setKey(uint8_t *key, int keySize)
{
    if((keySize != 128) && (keySize != 192) && (keySize != 256)) return false;
    this->keySize = keySize;
    this->key = key;
    return true;
}

bool KeyGenerator::calcKeys()
{
    if(keySize == 0) return false;
    int wordSize = keySize / 32;
    int roundSize;
    if(wordSize == 4) roundSize = 11;
    else if(wordSize == 6) roundSize = 13;
    else roundSize = 15;

    extendedKey = new uint8_t[16*roundSize-1];
    // fill extentedKey with original key
    for(int i=0;i<4*wordSize;i++)
    {
        extendedKey[i] = key[i];
    }


    for (int i=4*wordSize;i<16*roundSize-1;i+=4)
    {
        int nthBackStep = 4*wordSize;
        uint8_t nthBackWord[4] = {extendedKey[i-nthBackStep], extendedKey[i-nthBackStep+1],
                                 extendedKey[i-nthBackStep+2], extendedKey[i-nthBackStep+3]};

        if((i/4>=wordSize) && ((i/4)%wordSize==0))
        {
            //(i-1)th words shift left and change values with sbox table
            uint8_t backWord[4] = {sbox[extendedKey[i-3]], sbox[extendedKey[i-2]],
                                   sbox[extendedKey[i-1]], sbox[extendedKey[i-4]]};
            extendedKey[i] = nthBackWord[0] ^ backWord[0] ^ rcon[(i/4)/wordSize];
            extendedKey[i+1] = nthBackWord[1] ^ backWord[1];
            extendedKey[i+2] = nthBackWord[2] ^ backWord[2];
            extendedKey[i+3] = nthBackWord[3] ^ backWord[3];
        }
        else if((i/4>=wordSize) && (wordSize>6) && ((i/4)%wordSize==4))
        {
            // change values of (i-1)th words with sbox table
            uint8_t backWord[4] = {sbox[extendedKey[i-4]], sbox[extendedKey[i-3]],
                                   sbox[extendedKey[i-2]], sbox[extendedKey[i-1]]};
            extendedKey[i] = nthBackWord[0] ^ backWord[0];
            extendedKey[i+1] = nthBackWord[1] ^ backWord[1];
            extendedKey[i+2] = nthBackWord[2] ^ backWord[2];
            extendedKey[i+3] = nthBackWord[3] ^ backWord[3];
        }
        else
        {
            uint8_t backWord[4] = {extendedKey[i-4], extendedKey[i-3], extendedKey[i-2], extendedKey[i-1]};
            extendedKey[i] = nthBackWord[0] ^ backWord[0];
            extendedKey[i+1] = nthBackWord[1] ^ backWord[1];
            extendedKey[i+2] = nthBackWord[2] ^ backWord[2];
            extendedKey[i+3] = nthBackWord[3] ^ backWord[3];
        }
    }
    return true;
}
