#include "matrix.h"
#include <iostream>
#include <UnitTest++/UnitTest++.h>

struct MatrixStructure{
	Matrix m1, m2, m3, m4;
	MatrixStructure() : m1(5,5), m2(5,5,6.0), m3(5,3), m4(4,5,2.0){};
};

// 1
TEST(Init){
	try{
		Matrix m(-10,-1);
		//should not get here
		CHECK(true);
	} catch(InvalidArgument& ia){ CHECK(true); }
} 

// 2
TEST(initToZero){
	Matrix m(5,5);
	for(int i = 0; i < 25; ++i){
		CHECK_CLOSE(0, m.getMat()[i], 0.01);
	}
}

// 3
TEST(initToFive){
	Matrix m(5,5,5);
	for(int i = 0; i < 25; ++i){
		CHECK_CLOSE(5, m.getMat()[i], 0.01);
	}
}

// 4
TEST(Indexing){
	Matrix m(3,4);
	for(int i = 0; i < 12; ++i){
		m.getMat()[i] = i+1;
	}
	int k = 1;
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 4; ++j){
			CHECK_CLOSE(k++, m(i,j), 0.01);
		}
	}
}

// 5
TEST(IndexingOverSize){
	Matrix m(4,3);
	try{
		m(5,2) = 5;
		CHECK(false);
	} catch(InvalidArgument& ia){ CHECK(true); }
	try{
		m(-1,2) = 5;
		CHECK(false);
	} catch(InvalidArgument& ia){ CHECK(true); }
	try{
		m(0,10);
		CHECK(false);
	} catch(InvalidArgument& ia){ CHECK(true); }
	try{
		m(0, -5);
		CHECK(false);
	} catch(InvalidArgument& ia){ CHECK(true); }
	try{
		m(-2,-4);
		CHECK(false);
	} catch(InvalidArgument& ia){ CHECK(true); }
	try{
		m(8,8);
		CHECK(false);
	} catch(InvalidArgument& ia){ CHECK(true); }
}

int main(){
	return UnitTest::RunAllTests();
}
