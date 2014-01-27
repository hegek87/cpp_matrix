#ifndef MATRIX_H
#define MATRIX_H
#include "../vector3d/vector3d.h"
#include <vector>
#include <string>

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

class Matrix{
	private:
		int rows;
		int cols;
		std::vector<double> mat;
	public:
		Matrix(int, int);
		Matrix(int, int, double);
		Matrix(double **);
		
		Matrix(const Matrix&);
		~Matrix();
		
		Vector3d matrixMulVec(const Matrix&, const Vector3d&);
		Vector3d matrixMulDir(const Matrix&, const Vector3d&);
		Matrix operator+(const Matrix&);
		Matrix operator-(const Matrix&);
		Matrix operator*(const Matrix&);
		Matrix operator*(const double);
		double operator()(const int, const int) const;
		double& operator()(const int, const int);
		Matrix identity(int, int);
		Matrix inverse();
		std::vector<double>& getMat();
		bool equals(const Matrix&);
};
#endif
