#ifndef MATRIX_H
#define MATRIX_H
#include "../vector3d/vector3d.h"
#include <vector>
#include <string>
struct resultLU;

struct InvalidArgument : public std::exception{
	std::string message;
	InvalidArgument(std::string mes) : message(mes) {}
	~InvalidArgument() throw() {}
	const char *what() const throw(){ return message.c_str(); }
};

struct InvalidSize : public std::exception{
	std::string message;
	InvalidSize(std::string mes) : message(mes){}
	~InvalidSize() throw(){}
	const char *what() const throw(){ return message.c_str(); }
};

struct SingularMatrix : public std::exception{
	std::string message;
	SingularMatrix(std::string mes) : message(mes) {}
	~SingularMatrix() throw() {}
	const char *what() const throw(){ return message.c_str(); }
};

class Matrix{
	private:
		int rows;
		int cols;
		std::vector<double> mat;
	public:
		Matrix(int, int);
		Matrix(int, int, double);
		Matrix(int,int,std::vector<double>&);
		
		Matrix(const Matrix&);
		~Matrix();
		Matrix& operator=(Matrix);
		
		friend void swap(Matrix&,Matrix&);
		
		Vector3d matrixMulVec(const Matrix&, const Vector3d&);
		Vector3d matrixMulDir(const Matrix&, const Vector3d&);
		Matrix operator+(const Matrix&);
		Matrix operator-(const Matrix&);
		Matrix operator*(const Matrix&);
		Matrix operator*(const double);
		double operator()(const int, const int) const;
		double& operator()(const int, const int);
		static Matrix identity(int);
		Matrix inverse();
		std::vector<double>& getMat();
		bool equals(const Matrix&);
		
		double determinant();
		double cofactor(int,int);
		Matrix backSub(const Matrix);
		Matrix forwardSub(const Matrix);
		resultLU decomposeLU();
		void decomposeLUP();
		Matrix gaussianElimination();
};

struct resultLU{
	Matrix lower;
	Matrix upper;
	resultLU(Matrix lower, Matrix upper) : lower(lower), upper(upper){}
};
#endif
