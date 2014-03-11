#ifndef COUNTINGSORTER_H
#define COUNTINGSORTER_H

#include <cassert>

namespace ycg {

template <class T>
class CountingSorter {
public:
	template <class IntValConvertor> void operator() (T *array, int size, IntValConvertor cvt, int maxVal);
};

template <class T>
template <class IntValConvertor>
void CountingSorter<T>::operator() (T *array, int size, IntValConvertor cvt, int maxVal) {
	assert(maxVal > 0);
	int *counter = new int[maxVal];
	for(int i = 0; i < maxVal; ++i) {
		counter[i] = 0;
	}
	T *temp = new T[size];
	for(int i = 0; i < size; ++i) {
		temp[i] = array[i];
		++counter[cvt(array[i])];
	}
	for(int i = 1; i < maxVal; ++i) {
		counter[i] += counter[i-1];
	}
	for(int i = size - 1; i >= 0; --i){
		array[--counter[cvt(temp[i])]] = temp[i];
	}
	delete []temp;
	delete []counter;
}

} //~ namespace ycg

#endif // COUNTINGSORTER_H
