Overview
========

This class is a simple matrix class, it allows basic matrix operations, which are detailed below. The code here will be useful for linear algebra techniques which may arrive in graphics based programming. The matrix class gives the user the ability to test matrices for equality, add, subtract, multiply (by a scalar or another matrix), find an inverse, and easily access elements.

The matmain.cpp file contains unit tests used (UnitTest++) to test the code as it is being developed.

Basic Functionality
===================

Addition
--------
The + operator is overloaded to add two matrices of the same size. If an attempt to add two matrices of different sizes, an InvalidSize exception will be thrown.

Subtraction
-----------
The - operator has been overloaded to subtract two matrices, A and B (A-B). As with addition, if two matrices of differing sizes are subtracted, an exception will be thrown.

Indexing
--------
We have overridden () to index into our matrix in row major order (that is (a,b) accesses the element in row a, column b). The underlying data is not a two dimensional array and so we expect the user to use the () operator to get and change elements. If A is an mxn matrix, and we have i < 0 or i > m and j < 0 or j > n, then (i,j) will throw an exception.

Multiplication
--------------
We have overloaded * in two ways. For x, a real number, and A a matrix, we have x*A is the matrix B such that B_{i,j} = x*A_{i,j}. When multiplying two matrices A of size mxn and B of size kxl, we must have n=k, otherwise an exception will be thrown. The product, computed using Strassen's method will be an mxl matrix (and Strassen's method is O(n^2.807).

Multiply by 3d matrix
---------------------
We provide two methods for this, one multiplies the matrix by a 3 dimensional vector representing a direction vector, and the other represents multiplication by a 3 dimensional vector representing a point in 3-space. These both only work for a specif matrix size (4x4).

Equals
------
Determines whether two matrices A,B are equal. If the sizes aren't the same, it is clear that A!=B. Otherwise, we determine equality by checking each element in the matrices. We consider two elements equal if they are within 0.01 of eachother. That is, |A_{i,j}-B_{i,j}|<0.01, if this is not true for any (i,j) in {0,1,2,...,m-1}x{0,1,2,...,n-1}.

Identity
--------
This method returns an nxn identity matrix.

Inverse
-------
Computes the inverse of some matrix A (assuming it exists).
