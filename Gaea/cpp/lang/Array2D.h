#ifndef ARRAY2D_H
#define ARRAY2D_H

namespace ycg {

template <class T>
class Array2D {
public:
    Array2D(int rows, int cols);
    Array2D(int rows, int cols, const T& initVal);
    Array2D(const Array2D &another);
    ~Array2D();
    int rows() const;
    int cols() const;
    const T* operator[] (int i) const;
    T* operator[] (int i);
private:
    int _rows, _cols;
    int _size;
    T* data;
};

template <class T>
Array2D<T>::Array2D(int rows, int cols) {
    _rows = rows;
    _cols = cols;
    _size = rows * cols;
    data = new T[_size];
}

template <class T>
Array2D<T>::~Array2D() {
    delete []data;
}

template <class T>
inline const T* Array2D<T>::operator[] (int i) const {
    return data + i * _cols;
}

template <class T>
inline T* Array2D<T>::operator[] (int i) {
    return data + i * _cols;
}

template <class T>
inline int Array2D<T>::rows() const {
	return _rows;
}

template <class T>
inline int Array2D<T>::cols() const {
	return _cols;
}

} //~ namespace ycg

#endif // ARRAY2D_H
