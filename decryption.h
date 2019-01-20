#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <stdint.h>
#include "tables.h"
#include "keygenerator.h"

/**
 * @brief Dexryption class
 *
 */
class Decryption
{
public:
    /**
     * @brief Default constructer
     *
     */
    Decryption();
    /**
     * @brief Constructer
     *
     * @param message data pointer to be decrypted
     * @param key pointer of secret key
     * @param keySize size of key, must be 128, 192 or 256
     */
    Decryption(uint8_t* message, uint8_t* key, int keySize);
    /**
     * @brief Destructor
     *
     */
    ~Decryption();
    /**
     * @brief Decrypts data and return pointer of decrypted data,
     * only decrypts first 128 bit of data.
     *
     * @return uint8_t pointer of decrypted data
     */
    uint8_t* fastDecrypt();
    /**
     * @brief Set secret key
     *
     * @param key pointer of secret key
     * @param keySize size of key, must be 128, 192 or 256
     * @return bool if fail returns False otherwise return True
     */
    bool setKey(uint8_t* key, int keySize);
    /**
     * @brief Return pointer of decrypted message
     *
     * @return uint8_t pointer of decrypted message
     */
    uint8_t* getDecryptedMessage();
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
    BYTE *invSbox, *Xtime9, *XtimeB, *XtimeD, *XtimeE;
    void invShiftRows(uint8_t *data);
    void addRoundKey(uint8_t *data);
};

#endif // DECRYPTION_H
