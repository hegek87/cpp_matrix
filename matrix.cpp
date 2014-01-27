#include <iostream>
#include "matrix.h"


// creates a row x col zero matrix
Matrix::Matrix(int row, int col){
	this->rows = row; this->cols = col;
	this->mat = std::vector<double>(row * col);
	//initialize elements to zero
	for(int i = 0; i < this->rows; ++i){
		for(int j = 0; j < this->cols; ++j){
			mat[i*this->cols + j] = 0;
		}
	}
}

// creates a row x col matrix with val in each entry
Matrix::Matrix(int row, int col, double val){
	this->rows = row; this->cols = col;
	this->mat = std::vector<double>(row * col);
	//initialize elements to val
	for(int i = 0; i < this->rows; ++i){
		for(int j = 0; j < this->cols; ++j){
			mat[i*this->cols + j] = val;
		}
	}
}


double Matrix::operator()(const int i, const int j) const{
	return mat[i*this->cols + j];
}

double& Matrix::operator()(const int i, const int j){
	return mat[i*this->cols+j];
}

std::vector<double>& Matrix::getMat(){ return this->mat; }

Matrix::~Matrix(){
}	
