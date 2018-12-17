#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdint.h>
#include "tables.h"
#include "keygenerator.h"

typedef unsigned char BYTE;
extern BYTE sbox[256];
class Encryption
{
public:
    Encryption();
    Encryption(uint8_t* message, uint8_t* key, int keySize);
    ~Encryption();
    uint8_t* fastEncrypt();
    uint8_t* encrypt();
    bool setKey(uint8_t* key, int keySize);
    uint8_t* getEncryptedMessage();
    void setMessage(uint8_t *value);

private:
    KeyGenerator *keyGenarator;
    uint8_t* message;
    uint8_t* keys;
    int keySize, roundSize;
    BYTE *sbox, *Xtime2Sbox, *Xtime3Sbox;
    void subBytes();
    void shiftRows(uint8_t *data);
    void mixColumns();
    void addRoundKey(uint8_t *data);


};

#endif // ENCRYPTION_H
