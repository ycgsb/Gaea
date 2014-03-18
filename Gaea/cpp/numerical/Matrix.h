#ifndef MATRIX_H
#define MATRIX_H

#include "Common.h"
#include "Vector.h"
#include "../io/OutputStream.h"
#include <iostream>
#include <cassert>

namespace ycg {

class Matrix {
public:
	Matrix();
	Matrix(int rows, int cols, double initValue = 0.0);
	Matrix(int rows, int cols, bool needInit, double initValue = 0.0);
	Matrix(const Matrix& orig);
	Matrix(Matrix&& orig);
	explicit Matrix(const Vector& orig);
	explicit Matrix(Vector&& orig);
	~Matrix();
	Matrix& operator = (const Matrix& orig);
	Matrix& operator = (Matrix&& orig);
	operator Vector () const;
	int rows() const { return _rows; }
	int cols() const { return _cols; }
	double* operator [] (int i) { return _data + i*_cols; }
	const double* operator [] (int i) const { return _data + i*_cols; }
	double& operator () (int i, int j) { return _data[i*_cols + j]; }
	const double& operator () (int i, int j) const { return _data[i*_cols + j];	}
	bool isSquare() const { return _rows == _cols; }
	bool isEmpty() const { return _size == 0; }
	Matrix transpose() const;
	Matrix T() const { return transpose(); }
	Matrix inverse(int method = DECOMP_LU) const;
	Matrix inv(int method = DECOMP_LU) const { return inverse(method); }

	const Matrix& operator + () const;
    const Matrix  operator - () const;
    Matrix& operator += (const Matrix& rhs);
    Matrix& operator += (double rhs);
    Matrix& operator -= (const Matrix& rhs);
    Matrix& operator -= (double rhs);
    Matrix& operator *= (const Matrix& rhs);
    Matrix& operator *= (double rhs);
    Matrix& operator /= (double rhs);
	friend Matrix operator + (const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator + (const Matrix& lhs, double rhs);
    friend Matrix operator + (double lhs, const Matrix& rhs);
    friend Matrix operator - (const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator - (const Matrix& lhs, double rhs);
    friend Matrix operator - (double lhs, const Matrix& rhs);
    friend Matrix operator * (const Matrix& lhs, const Matrix& rhs);
    friend Vector operator * (const Matrix& lhs, const Vector& rhs);
    friend Matrix operator * (const Matrix& lhs, double rhs);
    friend Matrix operator * (double lhs, const Matrix& rhs);
    friend Matrix operator / (const Matrix& lhs, double rhs);
    friend bool operator == (const Matrix& lhs, const Matrix& rhs);
    friend bool operator != (const Matrix& lhs, const Matrix& rhs);


//    bool isNull() const;

////===================================================
//	Matrix dotProduct(const Matrix& rhs) const;

//	bool isSymmetric() const;
//	double trace() const;

    friend OutputStream& operator << (OutputStream& os, const Matrix& mat);
public:
    static Matrix rand(int rows, int cols);
    static Matrix eye(int n);
    static Matrix zeros(int rows, int cols);
    static Matrix ones(int rows, int cols);
protected:
	int _rows;
	int _cols;
	int _size;
	double *_data;
};

Matrix operator * (const Matrix& lhs, const Matrix& rhs);
Vector operator * (const Matrix& lhs, const Vector& rhs);

//inline bool Matrix::isNull() const {
//	return (rowNum == 0 && colNum == 0);
//}


//    double DefA(void);		//get the row-colum equation of matrix
//    double SubA(int, int);	//get the sub-row-colum equation of matrix

//ostream& operator << (ostream &os, Matrix &s)
//{
//  os<<"\n";
//  unsigned int l = s.Row[0]->GetLong();
//  for(int i=0; i<s.RowMax; i++)
//  {
//    double *value = (double*)*s.Row[i];
//    for(unsigned int j=0; j<l; j++)
//    {
//      os<<" ";
//      if(s.DataWitch != 0) os<<setw(s.DataWitch);
//	  if(s.DataPrec != 0) os<<setprecision(s.DataPrec);
//      os<<*(value+j);
//    }
//    os<<"\n";
//  }
//  return os;
//}
//istream& operator >> (istream &is, Matrix &s)
//{
//  for(int i=0; i<s.RowMax; i++)
//    is>>*s.Row[i];
//  return is;
//}

////other methods
//double Matrix::DefA(void)
//{
//  double Result=0;
//  if(ColMax!=RowMax || ColMax<1)
//  {
//    ErrSet(MT_ILL_METHOD);
//    return 0;
//  }
//  if(ColMax == 1)
//    return (*this)(1,1);
//  for(int i=1; i<=RowMax; i++)
//    Result += this->SubA(1,i)*(*this)(1,i);
//  return Result;
//}
//double Matrix::SubA(int i, int j)
//{
//  Matrix tmp(RowMax-1,ColMax-1);
//  int trow=1;
//  for(int row=1; row<=RowMax-1; row++)
//  {
//    int tcol=1;
//    if(trow == i) trow++;
//    for(int col=1; col<=ColMax-1; col++)
//    {
//      if(tcol == j) tcol++;
//      tmp(row,col) = (*this)(trow,tcol);
//      tcol++;
//    }
//    trow++;
//  }
//  return tmp.DefA()*pow(-1,i+j);
//}

//Matrix Matrix::Reverse(void)
//{
//  if(ColMax != RowMax)
//  {
//    ErrSet(MT_ILL_METHOD);
//    return *this;
//  }
//  if(this->DefA() == 0)
//  {
//    ErrSet(MT_ILL_METHOD);
//    return *this;
//  }
//  Matrix Result(RowMax,ColMax);
//  for(int row=1; row<=RowMax; row++)
//    for(int col=1; col<=ColMax; col++)
//      Result(row,col) = this->SubA(col,row);
//  return Result/this->DefA();
//}
//template <class T>
//bool isEqual(const Matrix<T>& src1, const Matrix<T>& src2) {
//	if(src1.rows!=src2.rows || src1.cols!=src2.cols) return false;
//	for (int i = 0; i < src1.size; ++i) {
//		if (src1.data[i]==src2.data[i]) continue;
//		return false;
//	}
//	return true;
//}
//

//void inputMatrixInt(Matrix<int>& matrix) {
//	for(int i = 0 ; i < matrix.size ; ++i)
//		scanf("%d", &matrix.data[i]);
//}

//	friend inline istream & operator >> (istream & is,Matrix & M)
//    friend inline ostream & operator << (ostream & os,const Matrix & M)
//    {
//        for(int r = 0 ; r < M.row ; r++)
//        {
//            cout << M[r][0] ;
//            for(int c = 1 ; c < M.col ; c++)
//                cout << ' ' << M[r][c] ;
//            cout << endl ;
//        }
//        return os;
//    }
//    Matrix & operator *= (Matrix M)
//    {
//        Matrix Res(row,M.col);
//        for(int i = 0 ; i < row ; i++)
//            for(int j = 0 ; j < M.col ; j++)
//                for(int k = 0 ; k < col ; k++)
//                    Res[j] += (Container[k] * M[k][j]);
//        return *this = Res ;
//    }

inline Matrix size(const Matrix& mat) {
	Matrix size(1, 2);
	size[0][0] = mat.rows();
	size[0][1] = mat.cols();
	return size;
}

inline int size(const Matrix& mat, int dim) {
	if (dim == 1) {
		return mat.rows();
	} else if (dim == 2) {
		return mat.cols();
	} else {
		return 1;
	}
}

} //~ namespace ycg

#endif // MATRIX_H
