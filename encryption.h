#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdint.h>
#include "tables.h"
#include "keygenerator.h"

typedef unsigned char BYTE;

/**
 * @brief Encryption class
 *
 */
class Encryption
{
public:
    /**
     * @brief Default constructer
     *
     */
    Encryption();
    /**
     * @brief Constructer
     *
     * @param message pointer of 128 bit data
     * @param key pointer of secret key
     * @param keySize size of key, must be 128, 192 or 256
     */
    Encryption(uint8_t* message, uint8_t* key, int keySize);
    /**
     * @brief Destructor
     *
     */
    ~Encryption();
    /**
     * @brief Encrypts data and return
     * pointer of encrypted data, only encrypts
     * first 128 bit of data
     *
     * @return uint8_t pointer of encrypted data
     */
    uint8_t* fastEncrypt();
    /**
     * @brief Set secret key
     *
     * @param key pointer of secret key
     * @param keySize size of key, must be 128, 192 or 256
     * @return bool if fail returns False otherwise return True
     */
    bool setKey(uint8_t* key, int keySize);
    /**
     * @brief Return pointer of encrypted data
     *
     * @return uint8_t pointer of encrypted data
     */
    uint8_t* getEncryptedMessage();
    /**
     * @brief Set message
     *
     * @param value pointer of message
     */
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
