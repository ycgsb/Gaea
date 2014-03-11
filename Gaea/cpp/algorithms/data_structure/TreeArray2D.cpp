#include "TreeArray2D.h"

namespace ycg {

TreeArray2D::TreeArray2D(int rows, int cols) {
    this->rowNum = rows;
    this->colNum = cols;
    int size = rows * cols;
    data = new int[size];
    for(int i = 0; i < size; ++i) {
        data[i] = 0;
    }
}

TreeArray2D::~TreeArray2D() {
    delete []data;
}

void TreeArray2D::modify(int r, int c, int delta){
    ++r; ++c;
    for(int i = r; i <= rowNum; i += lowbit(i))
        for(int j = c; j <= colNum; j += lowbit(j))
            data[(i - 1) * colNum + j - 1] += delta;
}

int TreeArray2D::sum(int r, int c) {
    ++r; ++c;
    int res = 0;
    for(int i = r; i >= 1; i -= lowbit(i))
        for(int j = c; j >= 1; j -= lowbit(j))
            res += data[(i - 1) * colNum + j - 1];
    return res;
}

} //~ namespace ycg
