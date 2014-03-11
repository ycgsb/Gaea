#ifndef LANG_H
#define LANG_H

namespace ycg {

template <class T>
inline void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void reverse(T* array, int size) {
	int mid = size / 2;
	for (int i = 0; i < mid; ++i) {
		swap(array[i], array[size-1-i]);
	}
}

} //~ namespace ycg
#endif // LANG_H
