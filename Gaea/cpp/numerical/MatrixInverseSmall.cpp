#include "MatrixInverseSmall.h"

namespace ycg {

MatrixInverseSmall::MatrixInverseSmall() { }

Matrix MatrixInverseSmall::invert(const Matrix& mat) const {
	switch (mat.rows()) {
		case 1:
			return invert1X1(mat);
		case 2:
			return invert2X2(mat);
		case 3:
			return invert3X3(mat);
		default:
			return Matrix::null();
	}
}

Matrix MatrixInverseSmall::invert1X1(const Matrix& mat) const {
	double x = mat[0][0];
	if (dblzero(x)) {
		return Matrix::null();
	}
	return Matrix(1, 1, 1.0 / x);
}

Matrix MatrixInverseSmall::invert2X2(const Matrix& mat) const {
	double a = mat[0][0], b = mat[0][1];
	double c = mat[1][0], d = mat[1][1];
	double det = a * d - c * b;
	if (dblzero(det)) {
		return Matrix::null();
	}
	Matrix inv(2, 2);
	inv[0][0] =  d / det; inv[0][1] = -b / det;
	inv[1][0] = -c / det; inv[1][1] =  a / det;
	return inv;
}

Matrix MatrixInverseSmall::invert3X3(const Matrix& mat) const {
	double a = mat[0][0], b = mat[0][1], c = mat[0][2];
	double d = mat[1][0], e = mat[1][1], f = mat[1][2];
	double g = mat[2][0], h = mat[2][1], i = mat[2][2];
	double det00 = e*i-h*f, det01 = d*i-g*f, det02 = d*h-g*e;
	double det10 = b*i-h*c, det11 = a*i-g*c, det12 = a*h-g*b;
	double det20 = b*f-e*c, det21 = a*f-d*c, det22 = a*e-d*b;
	double det = a*det00 - b*det01 + c*det02;
	if (dblzero(det)) {
		return Matrix::null();
	}
	Matrix inv(3, 3);
	inv[0][0] =  det00 / det; inv[0][1] = -det10 / det; inv[0][2] =  det20 / det;
	inv[1][0] = -det01 / det; inv[1][1] =  det11 / det; inv[1][2] = -det21 / det;
	inv[2][0] =  det02 / det; inv[2][1] = -det12 / det; inv[2][2] =  det22 / det;
	return inv;
}

} //~ namespace ycg
