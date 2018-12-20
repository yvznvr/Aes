#include <iostream>
#include <fstream>
#include <ctime>
#include "encryption.h"
#include "decryption.h"
#include <time.h>
using namespace std;

int main()
{

    uint8_t key[32] = {'a', 'y', 's', 'e', 't', 'a', 't', 'i', 'l', 'e', 'c', 'i', 'k', 't','i', 'i', 'y', 's', 'e', 't', 'a', 't', 'i', 'l', 'y', 's', 'e', 't', 'a', 't', 'i', 'l'};
    uint8_t message[16] = {'a', 'y', 's', 'e', 't', 'a', 't', 'i', 'l', 'e', 'c', 'i', 'k', 't','i', 'i'};

//    srand (time(NULL));
//    uint8_t arr[480*360*3];
//    for(int i=0;i<480*360*3;i++)
//    {
//        arr[i] = rand();
//    }

//    clock_t begin = clock();
//    Encryption en(arr,key,128);
//    for(int i=0;i<480*360;i+=128)
//    {
//        uint8_t* temp = en.fastEncrypt();
//        en.setMessage(arr);
//    }
//    clock_t end = clock();
//    double time = double(end-begin)/CLOCKS_PER_SEC;

    //https://kavaliro.com/wp-content/uploads/2014/03/AES.pdf
//    uint8_t key[16] =
//    {0x54,
//    0x68,
//    0x61,
//    0x74,
//    0x73,
//    0x20,
//    0x6D,
//    0x79,
//    0x20,
//    0x4B,
//    0x75,
//    0x6E,
//    0x67,
//    0x20,
//    0x46,
//    0x75};
//    uint8_t message[16] =
//    {0x54,
//    0x77,
//    0x6F,
//    0x20,
//    0x4F,
//    0x6E,
//    0x65,
//    0x20,
//    0x4E,
//    0x69,
//    0x6E,
//    0x65,
//    0x20,
//    0x54,
//    0x77,
//    0x6F};

//    Encryption en(message,key,128);
//    uint8_t* temp = en.fastEncrypt();
//    cout << "Encrypted Message:" << time << endl;
//    for(int i=0;i<16;i++) cout<<temp[i];
//    cout << endl;
//    Decryption de(temp, key, 128);
//    uint8_t* temp2 = de.fastDecrypt();
//    cout << "Decrypted Message:" << time << endl;
//    for(int i=0;i<16;i++) cout<<temp2[i];

    Encryption en(message,key,128);
    Decryption de(message, key, 128);
    uint8_t buffer[16];
    ifstream inputfile("test.jpg");
    ofstream enfile("encrypted.jpg");
    ofstream defile("decrypted.jpg");

    clock_t begin = clock();
    while(!inputfile.eof())
    {
        uint8_t *temp;
        inputfile.read((char*)buffer, 16);
        en.setMessage(buffer);
        temp = en.fastEncrypt();
        enfile.write((char*)temp, 16);
        de.setMessage(temp);
        temp = de.fastDecrypt();
        defile.write((char*)temp, 16);

    }
    clock_t end = clock();
    double time = double(end-begin)/CLOCKS_PER_SEC;

    cout << endl << "Time: " << time << endl;



    return 0;
}
