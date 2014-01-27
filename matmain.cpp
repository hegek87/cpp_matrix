#include "matrix.h"
#include <iostream>

int main(void){
	Matrix x(4, 4);
	x(1,0)=5;
	for(int i = 0; i < 16; ++i){
//		std::cout << x(i,j) << " ";
		std::cout << x.getMat()[i] << " ";
	}
	std::cout << std::endl;
}
