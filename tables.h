#ifndef TABLES_H
#define TABLES_H


typedef unsigned char BYTE;


/**
 * @brief Tables Class
 * contain some look up tables
 * for AES encryption and
 * decryption
 */
class Tables
{
public:
    /**
     * @brief constructer
     *
     */
    Tables();
    static BYTE sbox[256]; /**< Table for subbyte operation */
    static BYTE invSbox[256]; /**< Table for inverse subbyte operation */
    static BYTE Xtime2Sbox[256]; /**< Table that combine sbox table and 0x02 multiplication for mixcolumn and subbyte steps */
    static BYTE Xtime3Sbox[256]; /**< Table that combine sbox table and 0x03 multiplication for mixcolumn and subbyte steps */
    static BYTE Xtime9[256]; /**< Table that hold 0x09 multiplactions for inverse mix column */
    static BYTE XtimeB[256]; /**< Table that hold 0x0B multiplactions for inverse mix column */
    static BYTE XtimeD[256]; /**< Table that hold 0x0D multiplactions for inverse mix column */
    static BYTE XtimeE[256]; /**< Table that hold 0x0E multiplactions for inverse mix column */
    static BYTE rcon[16]; /**< Table that hold rcon numbers for key genaration */
};

#endif // TABLES_H
