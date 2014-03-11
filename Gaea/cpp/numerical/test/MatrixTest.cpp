#include "MatrixTest.h"
#include "../Matrix.h"
#include <cstdio>

namespace ycg {

MatrixTest::MatrixTest() { }

MatrixTest::~MatrixTest() { }

void MatrixTest::run() {
	Matrix A;
	Matrix B(2, 2);
	const Matrix C(2, 2, 4.2);
	Matrix D = Matrix::rand(2, 2);
	B[0][0] = 0.1; B[0][1] = 0.2;
	B[1][0] = 0.3; B[1][1] = 0.4;
	A = C + D;
	A = D - C;
	B = C * D;

	B = A + 2.5;
	B = 2.5 + A;
	B = A - 2.5;
	B = 2.5 - A;
	B = A * 2.5;
	B = 2.5 * A;
	B = A / 2.5;

	B = +A;
	D = -A;
	A += Matrix::ones(2, 2);
	A += 2.3;
	A -= Matrix::zeros(2, 2);
	A -= 3.4;
	A *= Matrix::eye(2);
	A *= 2.4;
	A /= 3.4;
//	A *= Matrix::rand(2, 2);

//	for(int n = 270; n <= 500;++n){
//		for (int t = 0; t < 1; ++t) {
//			Matrix a = Matrix::rand(n, n);
//			Matrix b = a.inv();
//			if (a*b == Matrix::eye(n)) {
//				printf("n = %d, case %d, test ok.\n", n, t);
//			} else {
//				printf("failed.\n");
//				printf("n = %d, case %d, test ok.\n", n, t);
////				printMatrix(a);
////				printMatrix(b);
////				printMatrix(a*b);
//				return 0;
//			}
//		}
//	}
	printf("Matrix Test passed.\n");
}

} //~ namespace ycg
