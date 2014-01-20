#ifndef MATRIX_H
#define MATRIX_H
#include "../vector3d/vector3d.h"
#include <vector>

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
		double operator()(const int, const int);
		Matrix identity(int, int);
		Matrix inverse();
};
#endif
