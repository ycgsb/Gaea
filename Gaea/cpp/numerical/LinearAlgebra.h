#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H

#include "Matrix.h"

namespace ycg {

namespace MatrixInverse {
	Matrix invertLUDecomp(const Matrix& mat);
	Matrix invert1X1(const Matrix& mat);
	Matrix invert2X2(const Matrix& mat);
	Matrix invert3X3(const Matrix& mat);
}

}  // namespace ycg
//double norm(Vector vec1, Vector vec2);



#endif // LINEARALGEBRA_H
