// Course:  CS213 - Programming II  - 2018
// Title:   Assignment I - Task 1 - Problem 2
// Program: CS213-2018-A1-T1-P2
// Purpose: Skeleton code for the student to start working
// Author:  Dr. Mohammad El-Ramly
// Date:    10 August 2018
// Version: 1.0

#include <iostream>
#include <iomanip>
#include <valarray>
//#include <cassert>

using namespace std;

// A structure to store a matrix
struct matrix
{
  valarray<int> data;       //valarray that will simulate matrix
  int row, col;
};
//Utilities
int plus(int x, int scaler) { return x+scaler;}
int multiply(int x, int scaler) { return x*scaler;}

// Already implemented
void createMatrix (int row, int col, int num[], matrix& mat);

// Student #1 with the smallest ID (e.g., 20170080)
// All these operations return a new matrix with the calculation result
matrix operator+  (matrix mat1, matrix mat2); // Add if same dimensions
matrix operator-  (matrix mat1, matrix mat2); // Sub if same dimensions
matrix operator*  (matrix mat1, matrix mat2); // Multi if col1 == row2
matrix operator+  (matrix mat1, int scalar);  // Add a scalar
matrix operator-  (matrix mat1, int scalar);  // Subtract a scalar
matrix operator*  (matrix mat1, int scalar);  // Multiple by scalar

// Student #2 with the middle ID (e.g., 20170082)
// The last operator >> takes an istream and a matrix and return the
// the same istream so it is possible to cascade input like
// cin >> matrix1 >> matrix2 << endl;
matrix operator+= (matrix& mat1, matrix mat2); // mat1 changes & return
					    // new matrix with the sum
matrix operator-= (matrix& mat1, matrix mat2); // mat1 changes + return new
					     // matrix with difference
matrix operator+= (matrix& mat, int scalar);   // change mat & return new matrix
matrix operator-= (matrix& mat, int scalar);   // change mat & return new matrix
void   operator++ (matrix& mat);   	// Add 1 to each element ++mat
void   operator-- (matrix& mat);    	// Sub 1 from each element --mat
istream& operator>> (istream& in, matrix& mat);
       	// Input matrix like this (dim 2 x 3) cin >> 2 3 4 6 8 9 12 123
       // and return istream to allow cascading input

//Student #3 with the biggest ID (e.g., 20170089)
ostream& operator<< (ostream& out, matrix mat);
       	// Print matrix  as follows (2 x 3)			4	 6 	  8
	       // and return ostream to cascade printing	9	12  	123
bool   operator== (matrix mat1, matrix mat2);	// True if identical
bool   operator!= (matrix mat1, matrix mat2); 	// True if not same
bool   isSquare   (matrix mat);  // True if square matrix
bool   isSymetric (matrix mat);  // True if square and symmetric
bool   isIdentity (matrix mat);  // True if square and identity
matrix transpose(matrix mat);    // Return new matrix with the transpose

//__________________________________________

int main()
{
  int data1 [] = {1,2,3,4,5,6,7,8};
  int data2 [] = {13,233,3,4,5,6};
  int data3 [] = {10,100,10,100,10,100,10,100};

  matrix mat1, mat2, mat3;
  createMatrix (4, 2, data1, mat1);
  createMatrix (2, 3, data2, mat2);
  createMatrix (4, 2, data3, mat3);

 //The next code will not work until you write the functions
  cout << mat1 << endl;
  cout << mat2 << endl;
  cout << mat3 << endl;

  cout << (mat1 + mat3) << endl << endl;
  cout << (mat3 + mat3) << endl << endl;

  ++mat1;
  cout << mat1 << endl;

  mat1+= mat3 += mat3;
  cout << mat1 << endl;
  cout << mat2 << endl;
  cout << mat3 << endl;
  // Add more examples of using matrix
  // .......

  return 0;
}

//__________________________________________
// Takes an array of data and stores in matrix according
// to rows and columns
void createMatrix (int row, int col, int num[], matrix& mat) {
  mat.row = row;
  mat.col = col;
  mat.data.resize (row * col);
  for (int i = 0; i < row * col; i++)
    mat.data [i] = num [i];
}
matrix operator+  (matrix mat1, matrix mat2){
    // Return a matrix containing the result of adding mat2 to mat1
    if( //Check if they got the same dimensions
            mat1.row != mat2.row
        and mat1.col != mat2.col
        )
        throw "Matrix addition error: matrix[1] and matrix[2] don't have the same dimensions";
    //Creating a temporary Array to hold the summation result,
    //it'll be used to create the new matrix
    int size = mat1.row*mat1.col;
    int resultArray [size];
    //Doing the sum
    for (int i = 0; i < size; ++i) {
        resultArray[i]= mat1.data[i] + mat2.data[i];
    }
    //Creating the new matrix with the temporary array values
    matrix returnMatrix;
    createMatrix(mat1.row, mat1.col,
                resultArray, returnMatrix);
    //Returning the result
    return returnMatrix;
}

matrix operator-  (matrix mat1, matrix mat2){
    // Return a matrix containing the result of subtracting mat2 from mat1
    if( //Check if they got the same dimensions
            mat1.row != mat2.row
            and mat1.col != mat2.col
            )
        throw "Matrix subtraction error: matrix[1] and matrix[2] don't have the same dimensions";
    //Creating a temporary Array to hold the subtraction result,
    //it'll be used to create the new matrix
    int size = mat1.row*mat1.col;
    int resultArray [size];
    //Getting the deference
    for (int i = 0; i < size; ++i) {
        resultArray[i]= mat1.data[i] - mat2.data[i];
    }
    //Creating the new matrix with the temporary array values
    matrix returnMatrix;
    createMatrix(mat1.row, mat1.col,
                 resultArray, returnMatrix);
    //Returning the result
    return returnMatrix;
}

matrix operator*  (matrix mat1, matrix mat2){
    //Returning a matrix with the result of multiplying mat1 by mat2
    if(mat1.col != mat2.row) throw "Matrix multiplication Error: matrix[1].col != matrix[2].row";
    //Creating a temporary Array to hold the multiplication result,
    //it'll be used to create the new matrix
    int size = mat1.row*mat2.col;
    int resultArray [size];
    //Local variable will be used in the operation
    int sum= 0;
    //Performing the operation
    for (int row = 0; row < mat1.row; ++row) {
        for (int colm = 0; colm < mat2.col; ++colm) {
            sum = 0;
            for (int k = 0; k < mat1.col; ++k) {
                sum += mat1.data[row*mat1.col + k] * mat2.data[k*mat2.col + colm];
            }
            resultArray[row*mat2.col + colm] = sum;
        }
    }
    //Creating the new matrix with the temporary array values
    matrix returnMatrix;
    createMatrix(mat1.row, mat1.col,
                 resultArray, returnMatrix);
    //Returning the result
    return returnMatrix;
}

matrix operator+  (matrix mat1, int scalar){
    //Return a matrix with mat1 values incremented by the scalar.

    //Creating a temporary Array to hold the summation result,
    //it'll be used to create the new matrix
    int size = mat1.row*mat1.col;
    int resultArray [size];
    for (int i = 0; i <size; ++i) {
        resultArray[i] = mat1.data[i]+scalar;
    }
    //Creating the new matrix with the temporary array values
    matrix returnMatrix;
    createMatrix(
            mat1.row, mat1.col,
            resultArray,returnMatrix
            );
    //Returning the result
    return returnMatrix;
}
matrix operator-  (matrix mat1, int scalar){
    //Return a matrix with mat1 values decreased by the scalar
    return mat1+(-1*scalar);
}
matrix operator*  (matrix mat1, int scalar){
    //Return a matrix with mat1 values multiplied by the scalar.

    //Creating a temporary Array to hold the summation result,
    //it'll be used to create the new matrix
    int size = mat1.row*mat1.col;
    int resultArray [size];
    for (int i = 0; i <size; ++i) {
        resultArray[i] = mat1.data[i]*scalar;
    }
    //Creating the new matrix with the temporary array values
    matrix returnMatrix;
    createMatrix(
            mat1.row, mat1.col,
            resultArray,returnMatrix
    );
    //Returning the result
    return returnMatrix;
}

matrix operator+= (matrix& mat1, matrix mat2){
    mat1 = mat1 + mat2;
    return mat1;
}

matrix operator-= (matrix& mat1, matrix mat2){
    mat1 = mat1 + mat2;
    return mat1;
}

matrix operator+= (matrix& mat, int scalar){
    mat = mat + scalar;
    return mat;
}
matrix operator-= (matrix& mat, int scalar){
    mat = mat - scalar;
    return mat;
}

void   operator++ (matrix& mat){
    mat = mat + 1;
}

void   operator-- (matrix& mat){
    mat = mat - 1;
}

istream& operator>> (istream& in, matrix& mat){
    int size = mat.row * mat.col;
    for (int i = 0; i < size; ++i) {
        in>>mat.data[i];
    }
    return in;
}

ostream& operator<< (ostream& out, matrix mat){
    for (int row = 0; row <mat.row ; ++row) {
        for (int col = 0; col < mat.col; ++col) {
            out<<mat.data[row*mat.col + col]<<" ";
        }
        out<<endl;
    }
    return out;
}

bool   operator== (matrix mat1, matrix mat2){
    if( //Check if they got the same dimensions
            mat1.row != mat2.row
            and mat1.col != mat2.col
            )
        return false;
    for (int i = 0; i <mat1.row*mat1.col ; ++i) {
        if (mat1.data[i] != mat2.data[i]) return false;
    }
    return true;
}
bool   operator!= (matrix mat1, matrix mat2){
    return not (mat1 == mat2);
}
bool   isSquare   (matrix mat){
    return mat.row == mat.col;
}
bool   isSymetric (matrix mat){
    if(not isSquare(mat)) return false;
    for (int row = 0; row < mat.row; ++row) {
        for (int col = 0; col < mat.col; ++col) {
            if (mat.data[row*mat.col+col] != mat.data[col*mat.col+row]) return false;
        }
    }
    return true;
}
bool   isIdentity (matrix mat){
    if(not isSquare(mat)) return false;
    for (int row = 0; row < mat.row; ++row) {
        for (int col = 0; col < mat.col; ++col) {
            if(row == col and mat.data [row*mat.col + col] != 1 ) return false;
            else if (row != col and mat.data [row*mat.col + col] != 0 ) return false;
        }
    }
    return true;
}

matrix transpose(matrix mat){
    int resultArray [mat.row*mat.col];
    for (int row = 0; row < mat.row; ++row) {
        for (int col = 0; col < mat.col; ++col) {
            resultArray[col*mat.col + row] = mat.data[row*mat.col + col];
        }
    }
    matrix returnMatrix;
    createMatrix(
            mat.row, mat.col,
            resultArray, returnMatrix
            );
    return returnMatrix;
}