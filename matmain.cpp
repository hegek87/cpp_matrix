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
		CHECK(false);
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

// 6
TEST(SetIndex){
	Matrix m(5,5);
	m(3,3) = 10000;
	CHECK_CLOSE(10000, m.getMat()[18], 0.01);
}

// 7
TEST(MatrixEquality){
	Matrix m1(5,5), m2(4,4), m3(5,4), m4(5,5);
	CHECK(m1.equals(m4));
	CHECK(!m1.equals(m2));
	CHECK(!m1.equals(m3));
	CHECK(!m2.equals(m3));
	CHECK(!m2.equals(m4));
	CHECK(!m3.equals(m4));
	
	Matrix m5(3,7,12), m6(3,7,12), m7(3,4,12), m8(3,4,7);
	CHECK(m5.equals(m6));
	CHECK(!m5.equals(m7));
	CHECK(!m7.equals(m8));
}

// 8
TEST(MatrixAddition){
	Matrix m1(5,5,10), m2(5,5,12), m3(4,4,2), m4(4,4);
	CHECK(Matrix(5,5,22).equals(m1+m2));
	try{
		Matrix t = m1+m3;
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	try{
		Matrix t = m1+m4;
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	try{
		Matrix t = m2+m3;
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	try{
		Matrix t = m2+m4;
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	CHECK(Matrix(4,4,2).equals(m3+m4));
}

TEST(MatrixSubtraction){
	Matrix m1(4,4,3), m2(4,4,5), m3(2,9, 109), m4(2,9);
	CHECK(Matrix(4,4,-2).equals(m1-m2));
	CHECK(Matrix(2,9,109).equals(m3-m4));
	try{
		Matrix t = m1-m3;
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	try{
		Matrix t = m1-m4;
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	try{
		Matrix t = m2-m3;
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	try{
		Matrix t = m2-m4;
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
}

int main(){
	return UnitTest::RunAllTests();
}
