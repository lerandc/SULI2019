#include <string>
#include <iostream>
#include <stdio.h>

int main(){

	std::string str_temp;
	char buffer[20];
	for(int i = 0; i < 1000; i++){
		sprintf(buffer,"%04d \n", i);
		str_temp = buffer;
		std::cout << str_temp;
	}

	int var = 0;
	int *pnt = &var;
	std::cout << pnt << std::endl;
	std::cout << *pnt << std::endl;

	return 0;
}