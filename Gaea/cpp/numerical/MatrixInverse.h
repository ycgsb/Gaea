#ifndef MATRIXINVERSE_H
#define MATRIXINVERSE_H

#include "Matrix.h"

namespace ycg {

class MatrixInverse {
public:
	MatrixInverse();
	virtual ~MatrixInverse() = 0;
	virtual Matrix invert(const Matrix& mat) const = 0;
};

} //~ namespace ycg

#endif // MATRIXINVERSE_H
