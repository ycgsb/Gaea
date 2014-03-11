#ifndef MATRIXCHAINMULTIPLICATION_H
#define MATRIXCHAINMULTIPLICATION_H

namespace ycg {

class MatrixDimension {
public:
    MatrixDimension(int rows, int cols) {

    }
};

class MatrixChainMultiplication
{
public:
    MatrixChainMultiplication(const int *matrixSize, int num);
    int minimumCost();
    void ConstructingOptimalSolution();
private:
    const int *matrixSize;
    int num;
};


} //~ namespace ycg

#endif // MATRIXCHAINMULTIPLICATION_H
