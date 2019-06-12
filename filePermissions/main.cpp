//test functions

#include "utility.h"
#include <string>
#include <iostream>

int main (){
    std::string test = "test.txt";
    bool answer = Prismatic::testWrite(test.c_str());
    bool answer2 = Prismatic::testExist(test.c_str());
    std::cout<< answer <<std::endl;
    std::cout<< answer2 <<std::endl;
    return 0;
}