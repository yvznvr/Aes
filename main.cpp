#include <iostream>
#include <ctime>
#include "encryption.h"
#include <time.h>
using namespace std;

int main()
{

    uint8_t key[32] = {'a', 'y', 's', 'e', 't', 'a', 't', 'i', 'l', 'e', 'c', 'i', 'k', 't','i', 'i', 'y', 's', 'e', 't', 'a', 't', 'i', 'l', 'y', 's', 'e', 't', 'a', 't', 'i', 'l'};
    uint8_t message[16] = {'a', 'y', 's', 'e', 't', 'a', 't', 'i', 'l', 'e', 'c', 'i', 'k', 't','i', 'i'};

    srand (time(NULL));
    uint8_t arr[480*360*3];
    for(int i=0;i<480*360*3;i++)
    {
        arr[i] = rand();
    }

    clock_t begin = clock();
    Encryption en(arr,key,128);
    for(int i=0;i<480*360;i+=128)
    {
        uint8_t* temp = en.fastEncrypt();
        en.setMessage(arr);
    }
    clock_t end = clock();
    double time = double(end-begin)/CLOCKS_PER_SEC;


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
//    Encryption en(message,key,256);
//    uint8_t* temp = en.fastEncrypt();
    cout << "Extented Key:" << time << endl;
//    for(int i=0;i<16;i++) cout<<temp[i];



    return 0;
}
