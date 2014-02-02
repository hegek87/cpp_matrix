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

Matrix::Matrix(const Matrix& copy) : rows(copy.rows), cols(copy.cols), 
mat(copy.mat){}

Matrix::~Matrix(){}
//Matrix& Matrix::operator=(Matrix other){}

Matrix::Matrix(int row, int col, std::vector<double>& matrix): rows(row), cols(col), mat(row*col,0){
	if(row < 0 || col < 0){
		throw InvalidArgument("Rows and Cols must be > 0\n");
	}
	std::copy(matrix.begin(), matrix.end(), this->mat.begin());
}

void swap(Matrix& first, Matrix& second){
	using std::swap;
	
	swap(first.rows, first.rows);
	swap(first.cols, second.cols);
	first.mat.swap(second.mat);
}

Matrix& Matrix::operator=(Matrix other){
	swap(*this, other);
	return *this;
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

/*
* For now an O(n^3) implementation works. Later we will implement 
* Strassen's algorithm for an O(2.8) implementation.
*/
Matrix Matrix::operator*(const Matrix& other){
	if(this->cols != other.rows){
		throw InvalidSize("Cannot multiply matrices");
	}
	Matrix res(this->rows, other.cols);
	// for each row in *this
	for(int i = 0; i < this->rows; ++i){
		// and for each col in other
		for(int j = 0; j < other.cols; ++j){
			//multiply the ith row and jth col and store in res(i,j)
			// this->cols == others.rows
			for(int k = 0; k < this->cols; ++k){
				res(i,j) += (*this)(i,k)*other(k,j);
			}
		}
	}
	return res;
}

double Matrix::determinant(){
	if(this->rows != this->cols){
		throw InvalidSize("Matrix must be square");
	}
	return 0;
}

Matrix Matrix::backSub(const Matrix ans){
	if(this->rows != this->cols){
		throw InvalidSize("Matrix must be square");
	}
	if(ans.rows != this->rows || ans.cols != 1){
		throw InvalidSize("The answer matrix is of wrong size");
	}
	int n = this->rows;
	std::vector<double> res(n);
	res[this->rows-1] = ans(this->rows-1,0)/(*this)(n-1,n-1);
	for(int i = n-2; i >= 0; --i){
		res[i] = ans(i,0);
		double temp = 0;
		for(int j = i+1; j < n; ++j){
			temp += (*this)(i,j)*res[j];
		}
		res[i] -= temp;
		res[i] /= (*this)(i,i);
	}
	return Matrix(n,1,res);
}

Matrix Matrix::forwardSub(const Matrix ans){
	if(this->rows != this->cols){
		throw InvalidSize("Matrix must be square");
	}
	if(ans.rows != this->rows || ans.cols != 1){
		throw InvalidSize("The answer matrix is of wrong size");
	}
	int n = this->rows;
	std::vector<double> res(n);
	res[0] = ans(0,0) / (*this)(0,0);
	for(int i = 1; i < n; ++i){
		res[i] = ans(i,0);
		double temp = 0;
		for(int j = 0; j < i; ++j){
			temp += (*this)(i,j)*res[j];
		}
		res[i] -= temp;
		res[i] /= (*this)(i,i);
	}
	return Matrix(n,1,res);
}

Matrix Matrix::identity(int size){
	Matrix id(size,size);
	for(int i = 0; i < size; ++i){
		id(i,i) = 1;
	}
	return id;
}

Matrix Matrix::operator*(const double factor){
	if(!factor){ return Matrix(rows,cols); }
	if(factor == 1){ return *this; }
	Matrix scaled(rows,cols);
	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			scaled(i,j) = (*this)(i,j)*factor;
		}
	}
	return scaled;
}

std::vector<double>& Matrix::getMat(){ return this->mat; }	
