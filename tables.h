#ifndef TABLES_H
#define TABLES_H

typedef unsigned char BYTE;


class Tables
{
public:
    Tables();
    static BYTE sbox[256];
    static BYTE Xtime2Sbox[256];
    static BYTE Xtime3Sbox[256];
    static BYTE rcon[16];
};

#endif // TABLES_H
