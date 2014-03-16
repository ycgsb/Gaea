#ifndef MATRIX_H
#define MATRIX_H

#include "Common.h"
#include "../io/OutputStream.h"
#include <cassert>

namespace ycg {

class Matrix {
public:
	Matrix();
	Matrix(int rows, int cols, double initValue = 0.0);
	Matrix(int rows, int cols, bool init, double initValue = 0.0);
	Matrix(const Matrix& mat);
	~Matrix();
	int rows() const;
	int cols() const;
	double* operator [] (int i);
	const double* operator [] (int i) const;
	double& operator () (int i, int j);
	const double& operator () (int i, int j) const;
    Matrix& operator = (const Matrix& rhs);
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
    friend Matrix operator * (const Matrix& lhs, double rhs);
    friend Matrix operator * (double lhs, const Matrix& rhs);
    friend Matrix operator / (const Matrix& lhs, double rhs);
    friend bool operator == (const Matrix& lhs, const Matrix& rhs);
    friend bool operator != (const Matrix& lhs, const Matrix& rhs);

    bool isSquare() const;
//    bool isNull() const;

//    Matrix inv(int method = DECOMP_LU) const;
////===================================================
//	Matrix dotProduct(const Matrix& rhs) const;
//	Matrix transpose() const;
//
//	bool isSymmetric() const;
//	double trace() const;

    friend OutputStream& operator << (OutputStream& os, const Matrix& mat);
public:
    static Matrix rand(int rows, int cols);
    static Matrix eye(int n);
    static Matrix zeros(int rows, int cols);
    static Matrix ones(int rows, int cols);
    static Matrix null();
private:
    void freeData();
protected:
	int rowNum;
	int colNum;
	double* data;
};

inline int Matrix::rows() const {
	return rowNum;
}

inline int Matrix::cols() const {
	return colNum;
}

inline double* Matrix::operator [] (int i) {
	return data + i*colNum;
}

inline const double* Matrix::operator [] (int i) const {
	return data + i*colNum;
}

inline double& Matrix::operator () (int i, int j) {
    return data[i*colNum + j];
}

inline const double& Matrix::operator () (int i, int j) const {
	return data[i*colNum + j];
}

inline bool Matrix::isSquare() const {
	return (rowNum == colNum);
}

//inline bool Matrix::isNull() const {
//	return (rowNum == 0 && colNum == 0);
//}


//    double DefA(void);		//get the row-colum equation of matrix
//    double SubA(int, int);	//get the sub-row-colum equation of matrix

////private copy and kill method
//void Matrix::Copy(Matrix &s)
//{
//  RowMax = s.RowMax;
//  ColMax = s.ColMax;
//  ErrHandler = s.ErrHandler;
//  if((Row=new DblArray* [RowMax]) == NULL)
//    ErrSet(MT_MEM_ALLOC);
//  for(int i=0; i<RowMax; i++)
//    if((Row[i]=new DblArray(*s.Row[i])) == NULL)
//      ErrSet(MT_MEM_ALLOC);
//}

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

//	friend inline istream & operator >> (istream & is,Matrix & M) //闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺�鐎氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏堕梺璺ㄥ枑閺嬪骞忛敓锟�/
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

inline bool isSquare(const Matrix& mat) {
	return mat.rows() == mat.cols();
}

} //~ namespace ycg

#endif // MATRIX_H
