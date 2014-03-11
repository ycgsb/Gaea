#ifndef RANGEMAXIMUMQUERYST_H
#define RANGEMAXIMUMQUERYST_H

#include <cmath>

namespace ycg {

template <class T>
class RangeMaximumQueryST {
public:
    RangeMaximumQueryST(const T* array, int n);
    ~RangeMaximumQueryST();
    void init();
    T queryMax(int left, int right);
private:
    const T* array;
    int n, m;
    T **table;
};

template <class T>
RangeMaximumQueryST<T>::RangeMaximumQueryST(const T *array, int n) {
    this->array = array;
    this->n = n;
    this->m = floor(log(static_cast<double>(n)) / log(2.0));
    table = new T*[m + 1];
    for (int i = 0; i <= m; ++i) {
        table[i] = new T[n];
    }
}

template <class T>
RangeMaximumQueryST<T>::~RangeMaximumQueryST() {
    for (int i = 0; i <= m; ++i) {
        delete []table[i];
    }
    delete []table;
}

template <class T>
void RangeMaximumQueryST<T>::init() {
    for(int j = 0; j < n; j++) {
        table[0][j] = array[j];
    }
    for(int i = 1; i <= m; ++i) {
        for(int j = n - 1; j >= 0; --j) {
            table[i][j] = table[i-1][j];
            int len = 1 << (i-1);
            if (j+len < n && table[i][j] < table[i-1][j+len])
                table[i][j] = table[i-1][j+len];
        }
    }
}

template <class T>
T RangeMaximumQueryST<T>::queryMax(int left, int right) {
    int m = floor(log(static_cast<double>(right-left+1)) / log(2.0));
    int len = 1 << m;
    if (table[m][right-len+1] < table[m][left]) {
        return table[m][left];
    } else {
        return table[m][right-len+1];
    }
}

} //~ namespace ycg

#endif // RANGEMAXIMUMQUERYST_H
