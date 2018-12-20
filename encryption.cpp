#include "encryption.h"


Encryption::Encryption()
{
    message = nullptr;
    keys = nullptr;
    keyGenarator = nullptr;
    keySize = roundSize = 0;
    sbox = Tables::sbox;
    Xtime2Sbox = Tables::Xtime2Sbox;
    Xtime3Sbox = Tables::Xtime3Sbox;
}

Encryption::Encryption(uint8_t *message, uint8_t *key, int keySize)
{
    setKey(key, keySize);
    this->message = message;
    sbox = Tables::sbox;
    Xtime2Sbox = Tables::Xtime2Sbox;
    Xtime3Sbox = Tables::Xtime3Sbox;
}

Encryption::~Encryption()
{
    delete keyGenarator;
}

uint8_t *Encryption::fastEncrypt()
{
    uint8_t temp[16];
    if((message==nullptr) || (keys==nullptr)) return 0;
    addRoundKey(message);
    keys += 16;
    for(int r=1;r<roundSize;r++)
    {

        temp[0] = Xtime2Sbox[message[0]] ^ Xtime3Sbox[message[5]] ^
                sbox[message[10]] ^ sbox[message[15]];
        temp[1] = sbox[message[0]] ^ Xtime2Sbox[message[5]] ^
                Xtime3Sbox[message[10]] ^ sbox[message[15]];
        temp[2] = sbox[message[0]] ^ sbox[message[5]] ^ Xtime2Sbox[message[10]] ^
                Xtime3Sbox[message[15]];
        temp[3] = Xtime3Sbox[message[0]] ^ sbox[message[5]] ^ sbox[message[10]] ^
                Xtime2Sbox[message[15]];

        temp[4] = Xtime2Sbox[message[4]] ^ Xtime3Sbox[message[9]] ^
                sbox[message[14]] ^ sbox[message[3]];
        temp[5] = sbox[message[4]] ^ Xtime2Sbox[message[9]] ^
                Xtime3Sbox[message[14]] ^ sbox[message[3]];
        temp[6] = sbox[message[4]] ^ sbox[message[9]] ^ Xtime2Sbox[message[14]] ^
                Xtime3Sbox[message[3]];
        temp[7] = Xtime3Sbox[message[4]] ^ sbox[message[9]] ^ sbox[message[14]] ^
                Xtime2Sbox[message[3]];

        temp[8] = Xtime2Sbox[message[8]] ^ Xtime3Sbox[message[13]] ^
                sbox[message[2]] ^ sbox[message[7]];
        temp[9] = sbox[message[8]] ^ Xtime2Sbox[message[13]] ^
                Xtime3Sbox[message[2]] ^ sbox[message[7]];
        temp[10] = sbox[message[8]] ^ sbox[message[13]] ^ Xtime2Sbox[message[2]] ^
                Xtime3Sbox[message[7]];
        temp[11] = Xtime3Sbox[message[8]] ^ sbox[message[13]] ^ sbox[message[2]] ^
                Xtime2Sbox[message[7]];

        temp[12] = Xtime2Sbox[message[12]] ^ Xtime3Sbox[message[1]] ^
                sbox[message[6]] ^ sbox[message[11]];
        temp[13] = sbox[message[12]] ^ Xtime2Sbox[message[1]] ^
                Xtime3Sbox[message[6]] ^ sbox[message[11]];
        temp[14] = sbox[message[12]] ^ sbox[message[1]] ^ Xtime2Sbox[message[6]] ^
                Xtime3Sbox[message[11]];
        temp[15] = Xtime3Sbox[message[12]] ^ sbox[message[1]] ^ sbox[message[6]] ^
                Xtime2Sbox[message[11]];
        addRoundKey(temp);
        keys += 16;
        for(int i=0;i<16;i++) message[i] = temp[i];
    }

    shiftRows(message);
    addRoundKey(message);
    keys -= roundSize*16;

    return message;
}

uint8_t *Encryption::encrypt()
{

}

bool Encryption::setKey(uint8_t *key, int keySize)
{
    this->keySize = keySize;
    if(keySize == 128) roundSize = 10;
    else if(keySize == 192) roundSize = 12;
    else if(keySize == 256) roundSize = 14;
    else return false;
    keyGenarator = new KeyGenerator(key, keySize);
    keyGenarator->calcKeys();
    keys = keyGenarator->getKey(0);
    return true;
}

uint8_t *Encryption::getEncryptedMessage()
{
    return message;
}

void Encryption::setMessage(uint8_t *value)
{
    message = value;
}

void Encryption::subBytes()
{

}

void Encryption::shiftRows(uint8_t *data)
{
    // replace first row with sbox value
    data[0] = sbox[data[0]]; data[4] = sbox[data[4]];
    data[8] = sbox[data[8]]; data[12] = sbox[data[12]];

    // 1 byte left shift and replace
    uint8_t tmp = sbox[data[1]]; data[1] = sbox[data[5]];
    data[5] = sbox[data[9]]; data[9] = sbox[data[13]]; data[13] = tmp;

    // 2 byte left shift and replace
    tmp = sbox[data[2]]; data[2] = sbox[data[10]]; data[10] = tmp;
    tmp = sbox[data[6]]; data[6] = sbox[data[14]];  data[14] = tmp;

    // 3 byte lefft shift and replace
    tmp = sbox[data[15]]; data[15] = sbox[data[11]];
    data[11] = sbox[data[7]]; data[7] = sbox[data[3]]; data[3] = tmp;
}

void Encryption::mixColumns()
{

}

void Encryption::addRoundKey(uint8_t *data)
{
    for(int i=0; i<16 ; i++)
    {
        data[i] ^= keys[i];
    }
}
