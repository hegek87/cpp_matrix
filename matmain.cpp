#include "matrix.h"
#include <iostream>

int main(void){
	Matrix x(4, 4, 1.0);
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 4; ++j){
			std::cout << x(i, j);
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}
