# Aes
Aes Encryption Decryption Libraries

You can encrypt or decrypt your files or datas with this library or you can see how to implement Aes Algorithm.

Encrypt and Decrypt Operation

    uint8_t key[16] = {'a', 's', 't', 'k', 'l', 'o', 'p', 'r', 'w', 'z', 'b', 'i', 'i', 'e','n', 'v'};
    uint8_t arr[480*360*3];  // data to be encrypt
    ... // fill arr
    Encryption en(arr,key,128);
    for(int i=0;i<480*360;i+=16)
    {
        uint8_t* temp = en.fastEncrypt(); // temp pointer and message pointer holds same address(no deepcopy)
        en.setMessage(arr+i);
    }
    
    // for decryption
    Decryption de(message, key, 128);
    for(int i=0;i<480*360;i+=16)
    {
        uint8_t* temp = de.fastDecrypt(); // temp pointer and message pointer holds same address(no deepcopy)
        de.setMessage(arr+i);
    }
    
You can see doxygen documentation in html folder.   
