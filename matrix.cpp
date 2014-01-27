#include <iostream>
#include <cmath>
#include "matrix.h"


// creates a row x col zero matrix
Matrix::Matrix(int row, int col) : rows(row), cols(col), mat(row*col, 0){
	if(row < 0 || col < 0){ 
		throw InvalidArgument("Rows and Cols must be > 0\n");
	}
}

// creates a row x col matrix with val in each entry
Matrix::Matrix(int row, int col, double val) : rows(row), cols(col), 
mat(row*col, val){
	if(row < 0 || col < 0){
		throw InvalidArgument("Rows and Cols must be > 0\n");
	}
}

// index into the ith row, jth column
double Matrix::operator()(const int i, const int j) const{
	if(i > this->rows || i < 0 || j < 0 || j > this->cols){
		throw InvalidArgument("Index too large");
	}
	return mat[i*this->cols + j];
}

// index into the ith row, jth column
double& Matrix::operator()(const int i, const int j){
	if(i > this->rows || i < 0 || j < 0 || j > this->cols){
		throw InvalidArgument("Index too large");
	}
	return mat[i*this->cols+j];
}

bool Matrix::equals(const Matrix& other){
	if(rows != other.rows || cols != other.cols){
		return false;
	}
	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			double diff = std::abs((*this)(i,j)-other(i,j));
			if(diff > 0.01){ return false; }
		}
	}
	return true;
}

Matrix Matrix::operator+(const Matrix& other){
	if(this->rows != other.rows || this->cols != other.cols){
		throw InvalidSize("Matrices are of different size");
	}
	Matrix t(this->rows, this->cols);
	for(int i = 0; i < this->rows; ++i){
		for(int j = 0; j < this->cols; ++j){
			t(i,j) = (*this)(i,j)+other(i,j);
		}
	}
	return t;
}

Matrix Matrix::operator-(const Matrix& other){
	if(this->rows != other.rows || this->cols != other.cols){
		throw InvalidSize("Matrices are of different size");
	}
	Matrix t(this->rows, this->cols);
	for(int i = 0; i < this->rows; ++i){
		for(int j = 0; j < this->cols; ++j){
			t(i,j) = (*this)(i,j)-other(i,j);
		}
	}
	return t;
}

std::vector<double>& Matrix::getMat(){ return this->mat; }

Matrix::~Matrix(){}	
