#include "LinearAlgebra.h"
#include "Common.h"
#include "Exception.h"
#include "../math/Math.h"
#include "../lang/Lang.h"

namespace ycg {

namespace MatrixInverse {

Matrix invertLUDecomp(const Matrix& mat) {
	assert(mat.isSquare() && !mat.isEmpty());
	static const double MIN_PIVOT = 2.22045e-016;
	int n = mat.rows();
	Matrix A = mat;
	Matrix B = Matrix::eye(n);
	for (int i = 0; i < n; i++) {
		double pivot = A[i][i];
		int k = i;
		for (int j = i + 1; j < n; j++) {
			if (Math::abs(A[j][i]) > Math::abs(pivot)) {
				pivot = A[j][i];
				k = j;
			}
		}
		if (Math::abs(pivot) < MIN_PIVOT) {
			throw SingularMatrixException();
		}
		if (k != i) {
			for (int j = 0; j < i; j++) {
				swap(B[i][j], B[k][j]);
			}
			for (int j = i; j < n; j++) {
				swap(A[i][j], A[k][j]);
				swap(B[i][j], B[k][j]);
			}
		}
		double d = -1.0 / pivot;
		for (int j = i + 1; j < n; j++) {
			double alpha = A[j][i] * d;
			for (int k = i + 1; k < n; k++) {
				A[j][k] += alpha * A[i][k];
			}
			for (int k = 0; k < n; k++) {
				B[j][k] += alpha * B[i][k];
			}
		}
		A[i][i] = -d;
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			double s = B[i][j];
			for (int k = i + 1; k < n; k++) {
				s -= A[i][k] * B[k][j];
			}
			B[i][j] = s * A[i][i];
		}
	}
	return B;
}

Matrix invert1X1(const Matrix& mat) {
	assert(mat.rows() == 1 && mat.cols() == 1);
	double a = mat[0][0];
	if (dblzero(a)) {
		throw SingularMatrixException();
	}
	return Matrix(1, 1, 1.0 / a);
}

Matrix invert2X2(const Matrix& mat) {
	assert(mat.rows() == 2 && mat.cols() == 2);
	double a = mat[0][0], b = mat[0][1];
	double c = mat[1][0], d = mat[1][1];
	double det = a * d - c * b;
	if (dblzero(det)) {
		throw SingularMatrixException();
	}
	Matrix inv(2, 2);
	inv[0][0] =  d / det; inv[0][1] = -b / det;
	inv[1][0] = -c / det; inv[1][1] =  a / det;
	return inv;
}

Matrix invert3X3(const Matrix& mat) {
	assert(mat.rows() == 3 && mat.cols() == 3);
	double a = mat[0][0], b = mat[0][1], c = mat[0][2];
	double d = mat[1][0], e = mat[1][1], f = mat[1][2];
	double g = mat[2][0], h = mat[2][1], i = mat[2][2];
	double det00 = e*i-h*f, det01 = d*i-g*f, det02 = d*h-g*e;
	double det10 = b*i-h*c, det11 = a*i-g*c, det12 = a*h-g*b;
	double det20 = b*f-e*c, det21 = a*f-d*c, det22 = a*e-d*b;
	double det = a*det00 - b*det01 + c*det02;
	if (dblzero(det)) {
		throw SingularMatrixException();
	}
	Matrix inv(3, 3);
	inv[0][0] =  det00 / det; inv[0][1] = -det10 / det; inv[0][2] =  det20 / det;
	inv[1][0] = -det01 / det; inv[1][1] =  det11 / det; inv[1][2] = -det21 / det;
	inv[2][0] =  det02 / det; inv[2][1] = -det12 / det; inv[2][2] =  det22 / det;
	return inv;
}

}  // namespace name

} //~ namespace ycg
