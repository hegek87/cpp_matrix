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

// 9
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

// 10
TEST(MatrixIdentity){
	Matrix m1(1,1,1), m2(2,2), m3(3,3), m4(4,4), m5(5,5),m6(6,6);
	m2(1,1)=m2(0,0)=1; m3(0,0)=m3(1,1)=m3(2,2)=1;
	m4(0,0)=m4(1,1)=m4(2,2)=m4(3,3)=1;
	m5(0,0)=m5(1,1)=m5(2,2)=m5(3,3)=m5(4,4)=1;
	m6(0,0)=m6(1,1)=m6(2,2)=m6(3,3)=m6(4,4)=m6(5,5)=1;
	CHECK(m1.equals(Matrix::identity(1)));
	CHECK(m2.equals(Matrix::identity(2)));
	CHECK(m3.equals(Matrix::identity(3)));
	CHECK(m4.equals(Matrix::identity(4)));
	CHECK(m5.equals(Matrix::identity(5)));
	CHECK(m6.equals(Matrix::identity(6)));
}

// 11
TEST(ScalarMult){
	Matrix m1(3,5,6), m2(109,2), m3(23,54,17),m4(5,5,1.5728573);
	CHECK(Matrix(3,5,12).equals(m1*2));
	CHECK(Matrix(3,5,60).equals(m1*10));	
	CHECK(Matrix(3,5,3).equals(m1*0.5));
	CHECK(Matrix(3,5,1.5).equals(m1*0.25));
	CHECK(Matrix(3,5,-12).equals(m1*-2));
	
	CHECK(Matrix(109,2).equals(m2*5));
	CHECK(Matrix(109,2).equals(m2*0));
	
	CHECK(Matrix(23,54,34).equals(m3*2));
	CHECK(Matrix(23,54,1).equals(m3*((1.0)/(17.0))));
	CHECK(Matrix(23,54,-17).equals(m3*-1));
	
	CHECK(Matrix(5,5).equals(m4*0));
	CHECK(Matrix(5,5,-1.5728573).equals(m4*-1));
	CHECK(Matrix(5,5,1.5728573).equals(m4*1));
	CHECK(Matrix(5,5,4.94128).equals(m4*3.14159265));
}
	
// 12
TEST(MatrixMult){
	Matrix m1(3,3,1),m2(3,4,5),m3(4,3,8),m4(5,7,1),m5(7,4,10);
	CHECK(Matrix(3,4,15).equals(m1*m2));
	try{
		m2*m1;
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	CHECK(Matrix(3,3,160).equals(m2*m3));
	CHECK(Matrix(5,4,70).equals(m4*m5));
	try{
		m4*m2;
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
}

// 13
TEST(CopyConstructor){
	Matrix m1(5,5,0), m2(m1), m3(m2),m4(1,2,5), m5(m4);
	CHECK(m1.equals(m2));
	CHECK(m2.equals(m3));
	CHECK(m3.equals(m1));
	CHECK(m4.equals(m5));
}

TEST(Assignment){
	Matrix m1(3,5,7), m2 = m1, m3(1,1), m4 = m3, m5(1,5,7), m6 = m5;
	CHECK(m1.equals(m2));
	CHECK(m3.equals(m4));
	CHECK(m5.equals(m6));
	
	Matrix m7 = m2=m1;
	CHECK(m7.equals(m1));
	CHECK(m2.equals(m1));
	CHECK(m7.equals(m2));
}

int main(){
	return UnitTest::RunAllTests();
}
