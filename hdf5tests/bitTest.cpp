#include <stdio.h>
#include <iostream>
#include <bitset>

int main(void){

    int dims[2] = {4,7};
    unsigned char wdata[4][7];
    int A,B,C,D;
    /*
    for (auto i = 0; i < 4; i++){
        for(auto j = 0; j < 7; j++){
            wdata[i][j] = 0;
            wdata[i][j] |= (i*j-j) * 0x03;
            wdata[i][j] |= (i & 0x03) << 3; 
            wdata[i][j] |= (j & 0x03) << 4;
            wdata[i][j] |= ( (i+j) & 0x03) << 6;
        }
    }

    int AA, BB, CC, DD;
    for(auto i = 0; i <dims[0]; i++){
        printf("[");
        for (auto j = 0; j < dims[1]; j++){
            AA = wdata[i][j] & 0x03;
            BB = (wdata[i][j] >> 2) & 0x03;
            CC = (wdata[i][j] >> 4) & 0x03;
            DD = (wdata[i][j] >> 6) & 0x03;
            printf(" {%d, %d, %d, %d}", AA,BB,CC,DD);
        }
        printf(" ]\n");
    }
    */

    unsigned short int F = 65535; 
    short int G = 5;

    //std::cout << F << " " << G << std::endl;

    //we have a 3 element long unsigned char array
    unsigned char store[3]; //24 bits total
    unsigned char one,two,three;

    //want to set two 10 bit integers, and one 4 bit electron count
    uint16_t X = 553; // (0000) (00)10 0010 1001
    uint16_t Y = 147; // (0000) (00)00 1001 0011
    uint16_t electron = 13; // (0000 0000 0000) 1101

    //copying a 10 bit integer would be & operation with 3FF, shift left by 2 
    uint16_t Xs = (X & 0x03ff) << 6;
    std::cout << Xs << " " << X << std::endl;

    std::cout << "X   = " << std::bitset<16>(X) << std::endl;
    std::cout << "Xs  = " << std::bitset<16>(Xs) << std::endl;

    //place shifted X into front of char array 
    store[0] = Xs >> 8;
    store[1] = Xs;

    std::cout << "st0 = " << std::bitset<8>(store[0]) << std::endl;
    std::cout << "st1 = " << std::bitset<8>(store[1]) << std::endl;
    
    //shift Y by 4 so that it fits into remainder of store[1]
    uint16_t Ys = (Y & 0x03ff) << 4;
    std::cout << "Y   = " << std::bitset<16>(Y) << std::endl;
    std::cout << "Ys  = " << std::bitset<16>(Ys) << std::endl;

    //place shifted Y into back of char array
    store[1] |= Ys >> 8;
    store[2] = Ys;

    std::cout << "st1 = " << std::bitset<8>(store[1]) << std::endl;
    std::cout << "st2 = " << std::bitset<8>(store[2]) << std::endl;

    //store electron count, no need to shift
    store[2] |= electron; 
    //end result should be X Y electron ie 1000 1010 01|00 1001 0011| 1101

    std::cout << "elec= " << std::bitset<16>(electron << 8) << std::endl;
    std::cout << "st2 = " << std::bitset<8>(store[2]) << std::endl;
    return 0;
}