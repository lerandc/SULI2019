#include "utility.h"
#include <string>
#include <iostream>
#ifdef _WIN32
   #include <io.h> 
   #define access    _access_s
#endif

namespace Prismatic {

    int testWrite(const std::string& filename){
        int answer = access(filename.c_str(),02);
        return answer;
    }
    int testExist(const std::string& filename){
        int answer = access(filename.c_str(),00);
        return answer;
    }
}