#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <stdint.h>
#include "tables.h"

typedef unsigned char BYTE;

/**
 * @brief Generates extended key for
 * AES 128, 192 and 256
 */
class KeyGenerator
{
public:
    /**
     * @brief Default Constructer
     * @see KeyGenerator
     */
    KeyGenerator();
    /**
     * @brief Constructer
     *
     * @param key pointer that holds secret key's address
     * @param keySize size of key, must be 128, 192 or 256
     */
    KeyGenerator(uint8_t* key, int keySize);
    /**
     * @brief Destructor
     *
     */
    ~KeyGenerator();
    /**
     * @brief return pointer that hold secret key
     * for specific round
     *
     * @param roundNumber specific round number
     * @return uint8_t pointer that hold roundkey's address
     */
    uint8_t* getKey(int roundNumber);
    /**
     * @brief set first secret key
     *
     * @param key pointer that holds secret key's address
     * @param keySize size of key, must be 128, 192 or 256
     * @return bool if fail returns False otherwise return True
     */
    bool setKey(uint8_t* key, int keySize);
    /**
     * @brief calculate extended key
     *
     * @return bool if fail returns False otherwise return True
     */
    bool calcKeys();
private:
    uint8_t* key;
    uint8_t* extendedKey;
    int keySize;
    BYTE *sbox, *rcon;
};

#endif // KEYGENERATOR_H
