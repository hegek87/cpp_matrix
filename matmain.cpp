#include "matrix.h"
#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include <vector>

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

// 14
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

// 15
TEST(VectorConstruct){
	std::vector<double> v1;
	for(int i = 0; i < 20; ++i){
		v1.push_back(i);
	}
	
	Matrix m1(5,4,v1);
	for(int i = 0; i < 5; ++i){
		for(int j = 0; j < 4; ++j){
			CHECK_CLOSE(v1[i*4+j],m1(i,j),0.01);
		}
	}
	
	std::vector<double> v2;
	Matrix m2(10,11,v2);
	CHECK(Matrix(10,11).equals(m2));
	
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 11; ++j){
			CHECK_CLOSE(0,m2(i,j),0.01);
		}
	}
}

// 16
TEST(Determinant){
	Matrix m1(2,2), m2(3,3,5), m3(4,5,0.2), m4(100,100,5);
	std::vector<double> matData;
	for(int i = 0; i < 36; ++i){ matData.push_back(i); }
	Matrix m5(6,6,matData);
	CHECK_CLOSE(0,m1.determinant(),0.01);
	//m2.decomposeLUP();
	//CHECK_CLOSE(0,m2.determinant(),0.01);
	try{
		m3.determinant();
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	std::vector<double> v6;
	v6.push_back(1);v6.push_back(2);v6.push_back(3);
	v6.push_back(2);v6.push_back(1);v6.push_back(6);
	v6.push_back(3);v6.push_back(8);v6.push_back(2);
	Matrix m6(3,3,v6);
	//CHECK_CLOSE(21, m6.determinant(), 0.01);
	std::vector<double> v1;
	v1.push_back(2);v1.push_back(3);v1.push_back(1);v1.push_back(5);
	v1.push_back(6);v1.push_back(13);v1.push_back(5);v1.push_back(19);
	v1.push_back(2);v1.push_back(19);v1.push_back(10);v1.push_back(23);
	v1.push_back(4);v1.push_back(10);v1.push_back(11);v1.push_back(31);
	Matrix m7(4,4,v1);
	CHECK_CLOSE(24, m7.determinant(), 0.01);
	
	CHECK_CLOSE(0,m4.determinant(),0.01);
	CHECK_CLOSE(0,m5.determinant(),0.01);

}

// 17
TEST(BackSub){
	Matrix m1(5,5), m2(6,6);
	Matrix a1(5,1), a2(6,1);
	Matrix x1(5,1), x2(6,1);
	
	for(int i = 0; i < 5; ++i){
		for(int j = 0; j < 5; ++j){
			if(i <= j){
				m1(i,j) = (i+1)*(j+1);
			}
		}
	}
	for(int i = 0; i < 6; ++i){
		for(int j = 0; j < 6; ++j){
			if(i <= j){
				m2(i,j) = (i+1)*(j+1);
			}
		}
	}
	x1(0,0)=70,x1(1,0)=50,x1(2,0)=200,x1(3,0)=115,x1(4,0)=100;
	a1(0,0) = 45, a1(1,0)=-(125.0/6.0), a1(2,0)=(455.0/36.0);
	a1(3,0)=(35.0/16.0), a1(4,0)=4;
	CHECK(a1.equals(m1.backSub(x1)));
	
	x2(0,0)=10,x2(1,0)=17,x2(2,0)=8,x2(3,0)=92,x2(4,0)=105,x2(5,0)=52;
	a2(0,0)=(3.0/2.0), a2(1,0)=(35.0/12.0),a2(2,0)=-(61.0/9.0);
	a2(3,0)=1.0/2.0,a2(4,0)=(37.0/15.0),a2(5,0)=(13.0/9.0);
	CHECK(a2.equals(m2.backSub(x2)));
	
	Matrix m4(3,2), m5(3,5);
	try{
		m4.forwardSub(Matrix(3,1));
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	try{
		m5.forwardSub(Matrix(3,1));
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	
	Matrix m6(3,3), m7(4,4);
	try{
		m6.forwardSub(Matrix(2,1));
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	try{
		m7.forwardSub(Matrix(4,2));
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
}

// 18
TEST(ForwardSub){
	Matrix m1(3,3),m2(4,4), m3(2,2);
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j){
			if(i >= j){
				m1(i,j) = (i+1)*(j+1);
			}
		}
	}
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 4; ++j){
			if(i >= j){
				m2(i,j) = (i+1)*(j+1);
			}
		}
	}
	for(int i = 0; i < 2; ++i){
		for(int j = 0; j < 2; ++j){
			if(i >= j){
				m3(i,j) = (i+1)*(j+1);
			}
		}
	}
	
	Matrix a1(3,1),a2(4,1),a3(2,1);
	Matrix x1(3,1),x2(4,1),x3(2,1);
	x1(0,0)=107.34,x1(1,0)=87.43,x1(2,0)=12.42;
	a1(0,0)=107.34,a1(1,0)=-31.8125,a1(2,0)=-13.1917;
	CHECK(a1.equals(m1.forwardSub(x1)));
	
	x2(0,0)=19,x2(1,0)=102.423,x2(2,0)=20,x2(3,0)=84;
	a2(0,0)=19,a2(1,0)=16.1058,a2(2,0)=-14.8483,a2(3,0)=3.58333;
	CHECK(a2.equals(m2.forwardSub(x2)));
	
	x3(0,0)=10,x3(1,0)=150;
	a3(0,0)=10,a3(1,0)=32.5;
	CHECK(a3.equals(m3.forwardSub(x3)));
	
	Matrix m4(3,2), m5(3,5);
	try{
		m4.forwardSub(Matrix(3,1));
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	try{
		m5.forwardSub(Matrix(3,1));
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	
	Matrix m6(3,3), m7(4,4);
	try{
		m6.forwardSub(Matrix(2,1));
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
	try{
		m7.forwardSub(Matrix(4,2));
		CHECK(false);
	} catch(InvalidSize is){ CHECK(true); }
}

// 19
TEST(LUDecompose){
	std::vector<double> v1;
	v1.push_back(2);v1.push_back(3);v1.push_back(1);v1.push_back(5);
	v1.push_back(6);v1.push_back(13);v1.push_back(5);v1.push_back(19);
	v1.push_back(2);v1.push_back(19);v1.push_back(10);v1.push_back(23);
	v1.push_back(4);v1.push_back(10);v1.push_back(11);v1.push_back(31);
	
	std::vector<double> v2;
	v2.push_back(1);v2.push_back(0);v2.push_back(0);v2.push_back(0);
	v2.push_back(3);v2.push_back(1);v2.push_back(0);v2.push_back(0);
	v2.push_back(1);v2.push_back(4);v2.push_back(1);v2.push_back(0);
	v2.push_back(2);v2.push_back(1);v2.push_back(7);v2.push_back(1);
	
	std::vector<double> v3;
	v3.push_back(2);v3.push_back(3);v3.push_back(1);v3.push_back(5);
	v3.push_back(0);v3.push_back(4);v3.push_back(2);v3.push_back(4);
	v3.push_back(0);v3.push_back(0);v3.push_back(1);v3.push_back(2);
	v3.push_back(0);v3.push_back(0);v3.push_back(0);v3.push_back(3);
	
	Matrix m1(4,4,v1),m2(4,4,v2),m3(4,4,v3),m4(4,4,v1);
	
	ResultLU dlu = m1.decomposeLU();
	CHECK(dlu.lower.equals(m2));
	CHECK(dlu.upper.equals(m3));
	CHECK(m4.equals(m1));
}

// 20
TEST(LUPDecompose){
	std::vector<double> v1;
	v1.push_back(2);v1.push_back(0);v1.push_back(2);v1.push_back(0.6);
	v1.push_back(3);v1.push_back(3);v1.push_back(4);v1.push_back(-2);
	v1.push_back(5);v1.push_back(5);v1.push_back(4);v1.push_back(2);
	v1.push_back(-1);v1.push_back(-2);v1.push_back(3.4);v1.push_back(-1);
	
	std::vector<double> v2;
	v2.push_back(1);v2.push_back(0);v2.push_back(0);v2.push_back(0);
	v2.push_back(0.4);v2.push_back(1);v2.push_back(0);v2.push_back(0);
	v2.push_back(-0.2);v2.push_back(0.5);v2.push_back(1);v2.push_back(0);
	v2.push_back(0.6);v2.push_back(0);v2.push_back(0.4);v2.push_back(1);
	
	std::vector<double> v3;
	v3.push_back(5);v3.push_back(5);v3.push_back(4);v3.push_back(2);
	v3.push_back(0);v3.push_back(-2);v3.push_back(0.4);v3.push_back(-0.2);
	v3.push_back(0);v3.push_back(0);v3.push_back(4);v3.push_back(-0.5);
	v3.push_back(0);v3.push_back(0);v3.push_back(0);v3.push_back(-3);
	
	Matrix m1(4,4,v1),m2(4,4,v2),m3(4,4,v3);
	ResultLUP res = m1.decomposeLUP();
	Matrix m4 = res.lu.lower, m5 = res.lu.upper;
	std::cout << "LOWER:" << std::endl;
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 4; ++j){
			std::cout << m4(i,j) << "\t ";
		}
		std::cout << std::endl;
	}
	std::cout << "UPPER:" << std::endl;
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 4; ++j){
			std::cout << m5(i,j) << "\t ";
		}
		std::cout << std::endl;
	}
	std::cout << "PERMUTATIONS:" << std::endl;
	for(int i = 0; i < 4; ++i){
		std::cout << res.permutation(i,0) << std::endl;
	}
	// construct permutation matrix
	Matrix p(4,4);
	for(int i = 0; i < 4; ++i){
		p(i,res.permutation(i,0)) = 1;
	}
	CHECK(m4.equals(m2));
	CHECK(m5.equals(m3));
	CHECK((p*m1).equals(m4*m5));
}

// 21
TEST(Sign){
	int p1[3] = {0,1,2}, p2[3] = {0,2,1}, p3[3] = {1,0,2};
	int p4[3] = {1,2,0}, p5[3] = {2,0,1}, p6[3] = {2,1,0};
	Matrix m1(3,3),m2(3,3),m3(3,3),m4(3,3),m5(3,3),m6(3,3);
	CHECK_CLOSE(1,m1.sign(),0.01);
	CHECK_CLOSE(-1,m2.sign(),0.01);
	CHECK_CLOSE(-1,m3.sign(),0.01);
	CHECK_CLOSE(1,m4.sign(),0.01);
	CHECK_CLOSE(1,m5.sign(),0.01);
	CHECK_CLOSE(-1,m6.sign(),0.01);
}
	
int main(){
	return UnitTest::RunAllTests();
}
