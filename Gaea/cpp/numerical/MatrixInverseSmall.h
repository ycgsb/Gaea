#ifndef MATRIXINVERSESMALL_H
#define MATRIXINVERSESMALL_H

#include "Matrix.h"
#include "MatrixInverse.h"

namespace ycg {

class MatrixInverseSmall : public MatrixInverse {
public:
	MatrixInverseSmall();
	Matrix invert(const Matrix& mat) const;
private:
	Matrix invert1X1(const Matrix& mat) const;
	Matrix invert2X2(const Matrix& mat) const;
	Matrix invert3X3(const Matrix& mat) const;
};

} //~ namespace ycg

#endif // MATRIXINVERSESMALL_H
