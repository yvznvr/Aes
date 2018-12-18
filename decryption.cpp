#include "decryption.h"

Decryption::Decryption()
{
    message = nullptr;
    keys = nullptr;
    keyGenarator = nullptr;
    keySize = roundSize = 0;
    invSbox = Tables::invSbox;
    Xtime9 = Tables::Xtime9;
    XtimeB = Tables::XtimeB;
    XtimeD = Tables::XtimeD;
    XtimeE = Tables::XtimeE;
}

Decryption::Decryption(uint8_t *message, uint8_t *key, int keySize)
{
    setKey(key, keySize);
    this->message = message;
    invSbox = Tables::invSbox;
    Xtime9 = Tables::Xtime9;
    XtimeB = Tables::XtimeB;
    XtimeD = Tables::XtimeD;
    XtimeE = Tables::XtimeE;
}

Decryption::~Decryption()
{
    delete keyGenarator;
}

uint8_t *Decryption::fastDecrypt()
{
    if((message==nullptr) || (keys==nullptr)) return 0;
    uint8_t temp[16];
    keys += roundSize*16;
    addRoundKey(message);
    invShiftRows(message);
    keys -= 16;
    for (int i=roundSize-1;i>0;i--)
    {
        addRoundKey(message);
        keys -= 16;
        // restore column 0
        temp[0] = XtimeE[message[0]] ^ XtimeB[message[1]] ^ XtimeD[message[2]] ^ Xtime9[message[3]];
        temp[5] = Xtime9[message[0]] ^ XtimeE[message[1]] ^ XtimeB[message[2]] ^ XtimeD[message[3]];
        temp[10] = XtimeD[message[0]] ^ Xtime9[message[1]] ^ XtimeE[message[2]] ^ XtimeB[message[3]];
        temp[15] = XtimeB[message[0]] ^ XtimeD[message[1]] ^ Xtime9[message[2]] ^ XtimeE[message[3]];

        // restore column 1
        temp[4] = XtimeE[message[4]] ^ XtimeB[message[5]] ^ XtimeD[message[6]] ^ Xtime9[message[7]];
        temp[9] = Xtime9[message[4]] ^ XtimeE[message[5]] ^ XtimeB[message[6]] ^ XtimeD[message[7]];
        temp[14] = XtimeD[message[4]] ^ Xtime9[message[5]] ^ XtimeE[message[6]] ^ XtimeB[message[7]];
        temp[3] = XtimeB[message[4]] ^ XtimeD[message[5]] ^ Xtime9[message[6]] ^ XtimeE[message[7]];

        // restore column 2
        temp[8] = XtimeE[message[8]] ^ XtimeB[message[9]] ^ XtimeD[message[10]] ^ Xtime9[message[11]];
        temp[13] = Xtime9[message[8]] ^ XtimeE[message[9]] ^ XtimeB[message[10]] ^ XtimeD[message[11]];
        temp[2]  = XtimeD[message[8]] ^ Xtime9[message[9]] ^ XtimeE[message[10]] ^ XtimeB[message[11]];
        temp[7]  = XtimeB[message[8]] ^ XtimeD[message[9]] ^ Xtime9[message[10]] ^ XtimeE[message[11]];

        // restore column 3
        temp[12] = XtimeE[message[12]] ^ XtimeB[message[13]] ^ XtimeD[message[14]] ^ Xtime9[message[15]];
        temp[1] = Xtime9[message[12]] ^ XtimeE[message[13]] ^ XtimeB[message[14]] ^ XtimeD[message[15]];
        temp[6] = XtimeD[message[12]] ^ Xtime9[message[13]] ^ XtimeE[message[14]] ^ XtimeB[message[15]];
        temp[11] = XtimeB[message[12]] ^ XtimeD[message[13]] ^ Xtime9[message[14]] ^ XtimeE[message[15]];

        for(int i=0;i<16;i++)
            message[i] = invSbox[temp[i]];
    }

    addRoundKey(message);
    keys += roundSize*16;
    return message;
}

bool Decryption::setKey(uint8_t *key, int keySize)
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

uint8_t *Decryption::getDecryptedMessage()
{
    return message;
}

void Decryption::setMessage(uint8_t *value)
{
    message = value;
}

void Decryption::invShiftRows(uint8_t *data)
{
    uint8_t temp;

    // invSbox[row(i)] i=1...n
    data[0] = invSbox[data[0]]; data[4] = invSbox[data[4]];
    data[8] = invSbox[data[8]]; data[12] = invSbox[data[12]];

    // 1 byte shift right and replace values wit invSbox
    temp = invSbox[data[13]]; data[13] = invSbox[data[9]];
    data[9] = invSbox[data[5]]; data[5] = invSbox[data[1]]; data[1] = temp;

    // 2 byte shift right and replace values wit invSbox
    temp = invSbox[data[2]]; data[2] = invSbox[data[10]]; data[10] = temp;
    temp = invSbox[data[6]]; data[6] = invSbox[data[14]]; data[14] = temp;

    // 3 byte shift right and replace values wit invSbox
    temp = invSbox[data[3]]; data[3] = invSbox[data[7]];
    data[7] = invSbox[data[11]]; data[11] = invSbox[data[15]]; data[15] = temp;
}

void Decryption::addRoundKey(uint8_t *data)
{
    for(int i=0; i<16 ; i++)
    {
        data[i] ^= keys[i];
    }
}
