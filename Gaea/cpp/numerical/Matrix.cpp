#include "Matrix.h"
#include "../util/Random.h"
#include "../io/Writer.h"

namespace ycg {

Matrix::Matrix():
	rowNum(0),
	colNum(0),
	data(nullptr) { }

Matrix::Matrix(int rows, int cols, double initValue) {
	rowNum = rows;
	colNum = cols;
	int length = rowNum*colNum;
	data = new double[length];
	for (int i = 0; i < length; ++i) {
		data[i] = initValue;
	}
}

Matrix::Matrix(int rows, int cols, bool init, double initValue) {
	rowNum = rows;
	colNum = cols;
	int length = rowNum*colNum;
	data = new double[length];
	if (init) {
		for (int i = 0; i < length; ++i) {
			data[i] = initValue;
		}
	}
}

Matrix::Matrix(const Matrix& mat) {
	rowNum = mat.rowNum;
	colNum = mat.colNum;
	int length = rowNum*colNum;
	data = new double[length];
	for (int i = 0; i < length; ++i) {
		data[i] = mat.data[i];
	}
}

Matrix::~Matrix() {
    freeData();
}

void Matrix::freeData() {
    delete []data;
    data = 0;
}

Matrix& Matrix::operator = (const Matrix& rhs) {
    if (this == &rhs) {
    	return *this;
    }
    rowNum = rhs.rowNum;
    colNum = rhs.colNum;
    if (data != 0) {
        freeData();
    }
    int length = rowNum*colNum;
    data = new double[length];
    for (int i = 0; i < length; ++i) {
        data[i] = rhs.data[i];
    }
    return *this;
}

const Matrix& Matrix::operator +() const {
	return *this;
}

const Matrix Matrix::operator -() const{
	Matrix result(rowNum, colNum, false);
	int length = result.rowNum * result.colNum;
	for (int i = 0; i < length; ++i) {
		result.data[i] = -data[i];
	}
	return result;
}

Matrix& Matrix::operator += (const Matrix& rhs) {
    assert(this->rows() == rhs.rows() && this->cols() == rhs.cols());
    int length = rowNum * colNum;
    for (int i = 0; i < length; ++i) {
    	data[i] += rhs.data[i];
    }
    return *this;
}

Matrix& Matrix::operator += (double rhs) {
    int length = rowNum * colNum;
    for (int i = 0; i < length; ++i) {
    	data[i] += rhs;
    }
    return *this;
}

Matrix& Matrix::operator -= (const Matrix& rhs) {
    assert(this->rows() == rhs.rows() && this->cols() == rhs.cols());
    int length = rowNum *colNum;
    for (int i = 0; i < length; ++i) {
    	data[i] -= rhs.data[i];
    }
    return *this;
}

Matrix& Matrix::operator -= (double rhs) {
    int length = rowNum * colNum;
    for (int i = 0; i < length; ++i) {
    	data[i] -= rhs;
    }
    return *this;
}

Matrix& Matrix::operator *=(const Matrix& rhs) {
	assert(this->cols() == rhs.rows());
	Matrix temp(*this);
	for(int i = 0; i < this->rowNum; ++i) {
		for(int j = 0; j < rhs.colNum; ++j) {
			double sum = 0;
			for(int k = 0; k < this->colNum; ++k) {
				sum += temp[i][k] * rhs[k][j];
			}
			this->data[i*colNum+j] = sum;
		}
	}
	return *this;
}

Matrix& Matrix::operator *= (double rhs) {
    int length = rowNum*colNum;
	for (int i = 0; i < length; ++i) {
		data[i] *= rhs;
    }
    return *this;
}

Matrix& Matrix::operator /= (double rhs) {
    int length = rowNum*colNum;
	for (int i = 0; i < length; ++i) {
		data[i] /= rhs;
    }
    return *this;
}

Matrix operator + (const Matrix& lhs, const Matrix& rhs) {
    assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols());
    Matrix result(lhs.rowNum, lhs.colNum, false);
    int length = result.rowNum * result.colNum;
    for (int i = 0; i < length; ++i) {
    	result.data[i] = lhs.data[i] + rhs.data[i];
    }
    return result;
}

Matrix operator + (const Matrix& lhs, double rhs) {
	Matrix result(lhs.rowNum, lhs.colNum);
	int length = result.rowNum * result.colNum;
    for (int i = 0; i < length; ++i) {
    	result.data[i] = lhs.data[i] + rhs;
    }
    return result;
}

Matrix operator + (double lhs, const Matrix& rhs) {
	return rhs + lhs;
}

Matrix operator - (const Matrix& lhs, const Matrix& rhs) {
	assert(lhs.rows() == rhs.rows() && lhs.cols()  == rhs.cols());
	Matrix result(lhs.rowNum, rhs.colNum, false);
	int length = result.rowNum * result.colNum;
	for (int i = 0; i < length; ++i) {
		result.data[i] = lhs.data[i] - rhs.data[i];
	}
	return result;
}

Matrix operator - (const Matrix& lhs, double rhs) {
	Matrix result(lhs.rowNum, lhs.colNum);
	int length = result.rowNum * result.colNum;
    for (int i = 0; i < length; ++i) {
    	result.data[i] = lhs.data[i] - rhs;
    }
    return result;
}

Matrix operator - (double lhs, const Matrix& rhs) {
	Matrix result(rhs.rowNum, rhs.colNum);
	int length = result.rowNum * result.colNum;
    for (int i = 0; i < length; ++i) {
    	result.data[i] = lhs - rhs.data[i];
    }
    return result;
}

Matrix operator * (const Matrix& lhs, const Matrix& rhs) {
	assert(lhs.cols() == rhs.rows());
	Matrix result(lhs.rowNum, rhs.colNum);
	for(int i = 0; i < result.rowNum; ++i) {
//		double* resultRowPtr =
		for(int j = 0; j < result.colNum; ++j) {
			double sum = 0;
			for(int k = 0; k < lhs.colNum; ++k) {
				sum += lhs[i][k] * rhs[k][j];
			}
			result[i][j] = sum;
		}
	}
	return result;
}

Matrix operator * (const Matrix& lhs, double rhs) {
	Matrix result(lhs.rowNum, lhs.colNum);
	int length = result.rowNum * result.colNum;
    for (int i = 0; i < length; ++i) {
    	result.data[i] = lhs.data[i] * rhs;
    }
    return result;
}

Matrix operator * (double lhs, const Matrix& rhs) {
	return rhs * lhs;
}

Matrix operator / (const Matrix& lhs, double rhs) {
	Matrix result(lhs.rowNum, lhs.colNum);
	int length = result.rowNum * result.colNum;
    for (int i = 0; i < length; ++i) {
    	result.data[i] = lhs.data[i] / rhs;
    }
    return result;
}

bool operator == (const Matrix& lhs, const Matrix& rhs) {
	if (lhs.rowNum != rhs.rowNum || lhs.colNum != rhs.colNum) {
		return false;
	}
	int length = lhs.rowNum * lhs.colNum;
	for (int i = 0; i < length; ++i) {
		if (dblNotEqual(lhs.data[i], rhs.data[i])) {
			return false;
		}
	}
	return true;
}

bool operator != (const Matrix& lhs, const Matrix& rhs) {
	return !(lhs==rhs);
}

OutputStream& operator << (OutputStream& os, const Matrix& mat) {
	double* dataPtr = mat.data;
	for(int i = 0 ; i < mat.rowNum ; ++i) {
		for(int j = 0 ; j < mat.colNum ; ++j) {
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
    	mat.data[i] = rnd.nextDouble();
    }
    return mat;
}

Matrix Matrix::eye(int n) {
    Matrix eye(n, n, 0.0) ;
    double* dataPtr = eye.data;
    for(int i = 0 ; i < n ; ++i) {
        *dataPtr = 1.0;
        dataPtr += (n+1);
    }
    return eye;
}

Matrix Matrix::zeros(int rows, int cols) {
    return Matrix(rows, cols, 0.0);
}

Matrix Matrix::ones(int rows, int cols) {
    return Matrix(rows, cols, 1.0);
}

Matrix Matrix::null() {
	return Matrix();
}
//Matrix Matrix::inv(int method) const {
//	assert(this->rows() == this->cols() && this->rows() > 0);
//	if (rowNum <= 3) {
//		static MatrixInverseSmall small;
//		return small.invert(*this);
//	}
//    if (method == DECOMP_LU) {
//    	static MatrixInverseLU lu;
//    	return lu.invert(*this);
//    }
//    return Matrix::null();
//}
//
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
//
//Matrix Matrix::transpose() const {
//	Matrix result(colNum, rowNum);
//	for(int i = 0; i < colNum; ++i) {
//		for(int j = 0; j < rowNum; ++j) {
//			result.data[i][j] = this->data[j][i];
//		}
//	}
//	return result;
//}
//
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
