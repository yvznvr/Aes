#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <stdint.h>
#include "tables.h"
#include "keygenerator.h"

class Decryption
{
public:
    Decryption();
    Decryption(uint8_t* message, uint8_t* key, int keySize);
    ~Decryption();
    uint8_t* fastDecrypt();
    bool setKey(uint8_t* key, int keySize);
    uint8_t* getDecryptedMessage();
    void setMessage(uint8_t *value);
private:
    KeyGenerator *keyGenarator;
    uint8_t* message;
    uint8_t* keys;
    int keySize, roundSize;
    BYTE *invSbox, *Xtime9, *XtimeB, *XtimeD, *XtimeE;
    void invShiftRows(uint8_t *data);
    void addRoundKey(uint8_t *data);
};

#endif // DECRYPTION_H
