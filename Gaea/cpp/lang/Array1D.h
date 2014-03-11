#ifndef ARRAY1D_H
#define ARRAY1D_H

namespace ycg {

template <class T>
class Array1D {
public:
	Array1D() : _size(0), _data(nullptr) { }
    Array1D(int size) :	_size(size), _data(new T[size]) { }
    Array1D(int size, const T& initVal);
    Array1D(const Array1D<T>& orig);
    Array1D(Array1D<T>&& orig);
    ~Array1D()  { delete []_data; }
    int size() const { return _size; }
    const T& operator [](int index) const { return _data[index]; }
    T& operator[](int index) { return _data[index]; }
    operator T* ()  { return _data; }
    T* begin() { return _data; }
    const T* begin() const { return _data; }
    T* end() { return _data + _size; }
    const T* end() const { return _data + _size; }
private:
    int _size;
    T *_data;
};

template <class T>
Array1D<T>::Array1D(int size, const T &initVal) :
	_size(size),
	_data(new T[size]) {
    for (int i = 0; i < size; ++i) {
        _data[i] = initVal;
    }
}

template <class T>
Array1D<T>::Array1D(const Array1D<T>& orig) :
	_size(orig._size),
	_data(new T[orig._size]) {
	for (int i = 0; i < _size; ++i) {
		_data[i] = orig._data[i];
	}
}

template <class T>
Array1D<T>::Array1D(Array1D<T>&& orig) :
	_size(orig._size),
	_data(orig._data) {
	orig._data = nullptr;
}

typedef Array1D<char> CharArray;
typedef Array1D<int> IntArray;
typedef Array1D<double> DoubleArray;
typedef Array1D<bool> BoolArray;

} //~ namespace ycg

#endif // ARRAY1D_H
