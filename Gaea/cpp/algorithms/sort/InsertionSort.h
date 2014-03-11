#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

namespace ycg {

template <class T>
class InsertionSort {
public:
    void operator() (T *array, int n);
};

template <class T>
void InsertionSort<T>::operator() (T *array, int n) {
    for(int j = 1; j < n; ++j) {
        int i = j - 1;
        T key = array[j];
        while(i >= 0 && key < array[i]) {
            array[i+1] = array[i];
            --i;
        }
        array[i+1] = key;
    }
}

} //~ namespace ycg

#endif // INSERTIONSORT_H
