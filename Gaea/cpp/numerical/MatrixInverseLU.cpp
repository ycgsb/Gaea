#include "MatrixInverseLU.h"
#include "../math/Math.h"
#include "../lang/Lang.h"

namespace ycg {

MatrixInverseLU::MatrixInverseLU() {
}

Matrix MatrixInverseLU::invert(const Matrix& mat) const {
	static const double MIN_PIVOT = 2.22045e-016;
	if (!mat.isSquare()) {
		return Matrix::null();
	}
	int n = mat.rows();
	Matrix A = mat;
	Matrix B = Matrix::eye(n);
	int i, j;
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
			return Matrix::null();
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

} //~ namespace ycg
