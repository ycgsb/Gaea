#ifndef TREEARRAY2D_H
#define TREEARRAY2D_H

namespace ycg {

class TreeArray2D {
public:
    TreeArray2D(int rows, int cols);
    ~TreeArray2D();
    int rows() const;
    int cols() const;
    void modify(int r, int c, int delta);
    int sum(int r, int c);
private:
    int lowbit(int x);
private:
    int* data;
    int rowNum, colNum;
};

inline int TreeArray2D::rows() const {
	return rowNum;
}

inline int TreeArray2D::cols() const {
	return colNum;
}

inline int TreeArray2D::lowbit(int x) {
    return x&(-x);
}

} //~ namespace ycg

#endif // TREEARRAY2D_H
