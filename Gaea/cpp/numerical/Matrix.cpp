#include "Matrix.h"
#include "LinearAlgebra.h"
#include "Exception.h"
#include "../util/Random.h"
#include "../io/Writer.h"

namespace ycg {

Matrix::Matrix():
	_rows(0),
	_cols(0),
	_size(0),
	_data(nullptr) { }

Matrix::Matrix(int rows, int cols, double initValue) :
	_rows(rows),
	_cols(cols),
	_size(rows * cols) {
	_data = new double[_size];
	for (int i = 0; i < _size; ++i) {
		_data[i] = initValue;
	}
}

Matrix::Matrix(int rows, int cols, bool needInit, double initValue) :
	_rows(rows),
	_cols(cols),
	_size(rows * cols) {
	_data = new double[_size];
	if (needInit) {
		for (int i = 0; i < _size; ++i) {
			_data[i] = initValue;
		}
	}
}

Matrix::Matrix(const Matrix& orig) :
	_rows(orig._rows),
	_cols(orig._cols),
	_size(orig._rows*orig._cols) {
	_data = new double[_size];
	for (int i = 0; i < _size; ++i) {
		_data[i] = orig._data[i];
	}
}

Matrix::Matrix(Matrix&& orig) :
	_rows(orig._rows),
	_cols(orig._cols),
	_size(orig._size),
	_data(orig._data) {
	orig._data = nullptr;
}

Matrix::Matrix(const Vector& orig) :
	_rows(orig._size),
	_cols(1),
	_size(orig._size) {
	_data = new double[_size];
	for (int i = 0; i < _size; ++i) {
		_data[i] = orig._data[i];
	}
}

Matrix::Matrix(Vector&& orig) :
	_rows(orig._size),
	_cols(1),
	_size(orig._size),
	_data(orig._data){
	orig._data = nullptr;
}

Matrix::~Matrix() {
    delete []_data;
}

Matrix& Matrix::operator = (const Matrix& orig) {
    if (this == &orig) return *this;
    _rows = orig._rows;
    _cols = orig._cols;
    _size = orig._size;
    delete []_data;
    _data = new double[_size];
    for (int i = 0; i < _size; ++i) {
        _data[i] = orig._data[i];
    }
    return *this;
}

Matrix& Matrix::operator = (Matrix&& orig) {
    if (this == &orig) return *this;
    _rows = orig._rows;
    _cols = orig._cols;
    _size = orig._size;
    _data = orig._data;
    orig._data = nullptr;
    return *this;
}

Matrix::operator Vector () const {
	Vector vec(_size, false);
	for (int i = 0; i < _size; ++i) {
		vec[i] = _data[i];
	}
	return vec;
}

Matrix Matrix::transpose() const {
	Matrix trans(_cols, _rows);
	for(int i = 0; i < _cols; ++i) {
		for(int j = 0; j < _rows; ++j) {
			trans._data[i * _rows + j] = _data[j * _cols + i];
		}
	}
	return trans;
}

Matrix Matrix::inverse(int method) const {
	assert(isSquare() && !isEmpty());
	switch (method) {
	case DECOMP_LU:
		if (_rows > 3) {
			return MatrixInverse::invertLUDecomp(*this);
		} else if (_rows == 3) {
			return MatrixInverse::invert3X3(*this);
		} else if (_rows == 2) {
			return MatrixInverse::invert2X2(*this);
		} else {
			return MatrixInverse::invert1X1(*this);
		}
	default:
		throw UnsupportMethodException();
	}
}

const Matrix& Matrix::operator +() const {
	return *this;
}

const Matrix Matrix::operator -() const{
	Matrix result(_rows, _cols, false);
	int length = result._rows * result._cols;
	for (int i = 0; i < length; ++i) {
		result._data[i] = -_data[i];
	}
	return result;
}

Matrix& Matrix::operator += (const Matrix& rhs) {
    assert(this->rows() == rhs.rows() && this->cols() == rhs.cols());
    int length = _rows * _cols;
    for (int i = 0; i < length; ++i) {
    	_data[i] += rhs._data[i];
    }
    return *this;
}

Matrix& Matrix::operator += (double rhs) {
    int length = _rows * _cols;
    for (int i = 0; i < length; ++i) {
    	_data[i] += rhs;
    }
    return *this;
}

Matrix& Matrix::operator -= (const Matrix& rhs) {
    assert(this->rows() == rhs.rows() && this->cols() == rhs.cols());
    int length = _rows *_cols;
    for (int i = 0; i < length; ++i) {
    	_data[i] -= rhs._data[i];
    }
    return *this;
}

Matrix& Matrix::operator -= (double rhs) {
    int length = _rows * _cols;
    for (int i = 0; i < length; ++i) {
    	_data[i] -= rhs;
    }
    return *this;
}

Matrix& Matrix::operator *=(const Matrix& rhs) {
	assert(this->cols() == rhs.rows());
	Matrix temp(*this);
	for(int i = 0; i < this->_rows; ++i) {
		for(int j = 0; j < rhs._cols; ++j) {
			double sum = 0;
			for(int k = 0; k < this->_cols; ++k) {
				sum += temp[i][k] * rhs[k][j];
			}
			this->_data[i*_cols+j] = sum;
		}
	}
	return *this;
}

Matrix& Matrix::operator *= (double rhs) {
    int length = _rows*_cols;
	for (int i = 0; i < length; ++i) {
		_data[i] *= rhs;
    }
    return *this;
}

Matrix& Matrix::operator /= (double rhs) {
    int length = _rows*_cols;
	for (int i = 0; i < length; ++i) {
		_data[i] /= rhs;
    }
    return *this;
}

Matrix operator + (const Matrix& lhs, const Matrix& rhs) {
    assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols());
    Matrix result(lhs._rows, lhs._cols, false);
    int length = result._rows * result._cols;
    for (int i = 0; i < length; ++i) {
    	result._data[i] = lhs._data[i] + rhs._data[i];
    }
    return result;
}

Matrix operator + (const Matrix& lhs, double rhs) {
	Matrix result(lhs._rows, lhs._cols);
	int length = result._rows * result._cols;
    for (int i = 0; i < length; ++i) {
    	result._data[i] = lhs._data[i] + rhs;
    }
    return result;
}

Matrix operator + (double lhs, const Matrix& rhs) {
	return rhs + lhs;
}

Matrix operator - (const Matrix& lhs, const Matrix& rhs) {
	assert(lhs.rows() == rhs.rows() && lhs.cols()  == rhs.cols());
	Matrix result(lhs._rows, rhs._cols, false);
	int length = result._rows * result._cols;
	for (int i = 0; i < length; ++i) {
		result._data[i] = lhs._data[i] - rhs._data[i];
	}
	return result;
}

Matrix operator - (const Matrix& lhs, double rhs) {
	Matrix result(lhs._rows, lhs._cols);
	int length = result._rows * result._cols;
    for (int i = 0; i < length; ++i) {
    	result._data[i] = lhs._data[i] - rhs;
    }
    return result;
}

Matrix operator - (double lhs, const Matrix& rhs) {
	Matrix result(rhs._rows, rhs._cols);
	int length = result._rows * result._cols;
    for (int i = 0; i < length; ++i) {
    	result._data[i] = lhs - rhs._data[i];
    }
    return result;
}

Matrix operator * (const Matrix& lhs, const Matrix& rhs) {
	assert(lhs.cols() == rhs.rows());
	Matrix result(lhs.rows(), rhs.cols());
	for(int i = 0; i < result.rows(); ++i) {
		for(int j = 0; j < result.cols(); ++j) {
			double sum = 0;
			for(int k = 0; k < lhs.cols(); ++k) {
				sum += lhs[i][k] * rhs[k][j];
			}
			result[i][j] = sum;
		}
	}
	return result;
}

Vector operator *(const Matrix& lhs, const Vector& rhs) {
	assert(lhs.cols() == rhs.size());
	Vector result(lhs.rows(), false);
	for (int i = 0; i < result.size(); ++i) {
		double sum = 0.0;
		for (int k = 0; k < rhs.size(); ++k) {
			sum += lhs[i][k]*rhs[k];
		}
		result[i] = sum;
	}
	return result;
}

Matrix operator * (const Matrix& lhs, double rhs) {
	Matrix result(lhs._rows, lhs._cols);
	int length = result._rows * result._cols;
    for (int i = 0; i < length; ++i) {
    	result._data[i] = lhs._data[i] * rhs;
    }
    return result;
}

Matrix operator * (double lhs, const Matrix& rhs) {
	return rhs * lhs;
}

Matrix operator / (const Matrix& lhs, double rhs) {
	Matrix result(lhs._rows, lhs._cols);
	int length = result._rows * result._cols;
    for (int i = 0; i < length; ++i) {
    	result._data[i] = lhs._data[i] / rhs;
    }
    return result;
}

bool operator == (const Matrix& lhs, const Matrix& rhs) {
	if (lhs._rows != rhs._rows || lhs._cols != rhs._cols) {
		return false;
	}
	int length = lhs._rows * lhs._cols;
	for (int i = 0; i < length; ++i) {
		if (dblNotEqual(lhs._data[i], rhs._data[i])) {
			return false;
		}
	}
	return true;
}

bool operator != (const Matrix& lhs, const Matrix& rhs) {
	return !(lhs==rhs);
}

OutputStream& operator << (OutputStream& os, const Matrix& mat) {
	double* dataPtr = mat._data;
	for(int i = 0 ; i < mat._rows ; ++i) {
		for(int j = 0 ; j < mat._cols ; ++j) {
			os << *dataPtr++ << " ";
		}
		os << '\n';
	}
	return os;
}

Matrix Matrix::rand(int rows, int cols) {
    Matrix mat(rows, cols);
    Random& rnd = Random::instance();
    int length = rows * cols;
    for (int i = 0; i < length; ++i) {
    	mat._data[i] = rnd.nextDouble();
    }
    return mat;
}

Matrix Matrix::eye(int n) {
    Matrix eye(n, n, 0.0) ;
    for(int i = 0 ; i < n ; ++i) {
        eye[i][i] = 1.0;
    }
    return eye;
}

Matrix Matrix::zeros(int rows, int cols) {
    return Matrix(rows, cols, 0.0);
}

Matrix Matrix::ones(int rows, int cols) {
    return Matrix(rows, cols, 1.0);
}

//Matrix Matrix::dotProduct(const Matrix& rhs) const {
//	assert(this->rows() == rhs.rows() && this->cols()  == rhs.cols());
//	Matrix result(rowNum, colNum);
//	for (int i = 0; i < rowNum; ++i) {
//		for (int j = 0; j < colNum; ++j) {
//			result.data[i][j] = this->data[i][j] * rhs.data[i][j];
//		}
//	}
//	return result;
//}

//bool Matrix::isSymmetric() const  {
//	if (!isSquare()) {
//		return false;
//	}
//	for(int i = 0; i < rowNum; ++i) {
//		for(int j = i + 1; j < rowNum; ++j) {
//            if (!dblequal(data[i][j], data[j][i])) {
//				return false;
//			}
//		}
//	}
//	return true;
//}
//
//double Matrix::trace() const {
//	assert(this->isSquare());
//	double sum = 0.0;
//	for (int i = 0; i < rowNum; ++i) {
//		sum += this->data[i][i];
//	}
//	return sum;
//}
//
//Matrix Matrix::operator / (double d) const {
//    assert(!dblzero(d));
//	Matrix result(rowNum, colNum);
//	for (int i = 0; i < rowNum; ++i) {
//		for (int j = 0; j < colNum; ++j) {
//			result.data[i][j] = data[i][j] / d;
//		}
//	}
//	return result;
//}


} //~ namespace ycg
