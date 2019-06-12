#include <stdio.h>
#include <iostream>
#include <bitset>

void storeSparse(unsigned char* store, const uint16_t X, const uint16_t Y, const uint16_t N){
    *store++ = (X & 0x03ff) >> 2;
    *store++ = ((X & 0x03ff) << 6) | (Y >> 4);
    *store = (Y << 4) | N;
}

void readSparse(unsigned char* store, uint16_t* X, uint16_t* Y, uint16_t* N){
    *X = ((*store++ << 2) & 0xffff);
    *X |= ((*store >> 6) & 0x0003); 
    *Y = ((*store++ << 4) & 0x03ff);
    *Y |= ((*store >> 4) & 0x000f);
    *N = *store & 0x000f;
}

int main(void){
    //we have a 3 element long unsigned char array
    unsigned char store[3]; //24 bits total

    //want to set two 10 bit integers, and one 4 bit electron count
    uint16_t X = 553; // (0000) (00)10 0010 1001
    uint16_t Y = 147; // (0000) (00)00 1001 0011
    uint16_t N = 13; // (0000 0000 0000) 1101


    //end result should be X Y electron ie 1000 1010 01|00 1001 0011| 1101
    unsigned char* store_pointer = &store[0];
    storeSparse(store_pointer, X,Y,N);

    uint16_t testX, testY, testN;
    uint16_t* Xpt = &testX;
    uint16_t* Ypt = &testY;
    uint16_t* Npt = &testN;

    unsigned char* read_pointer = &store[0];
    readSparse(read_pointer,Xpt,Ypt,Npt);

    std::cout << "X original: " << X << " || X read from sparse storage: " << testX << std::endl;
    std::cout << "Y original: " << Y << " || Y read from sparse storage: " << testY << std::endl;
    std::cout << "N original: " << N << "  || N read from sparse storage: " << testN << std::endl;

    return 0;
}