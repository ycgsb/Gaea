#ifndef MATRIXINVERSELU_H
#define MATRIXINVERSELU_H

#include "Matrix.h"
#include "MatrixInverse.h"

namespace ycg {

class MatrixInverseLU : public MatrixInverse {
public:
	MatrixInverseLU();
	Matrix invert(const Matrix& mat) const;
};

} //~ namespace ycg

#endif // MATRIXINVERSELU_H
