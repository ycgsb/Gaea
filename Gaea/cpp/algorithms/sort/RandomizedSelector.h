#ifndef RANDOMIZEDSELECTOR_H
#define RANDOMIZEDSELECTOR_H

#include "Comparator.h"
#include "../../util/Random.h"

namespace ycg {

template<class T>
class RandomizedSelector {
public:
	T operator() (T *array, int size, int k);
	template <class Comparator> T operator() (T *array, int size, int k, Comparator cmp);
private:
	template <class Comparator> T select(T *array, int left, int right, int k, Comparator cmp);
	template <class Comparator> int partition(T *array, int left, int right, Comparator cmp);
};

template <class T>
inline T RandomizedSelector<T>::operator() (T *array, int size, int k) {
	ComparatorLess<T> cmp;
	return select(array, 0, size-1, k, cmp);
}

template <class T>
template <class Comparator>
T RandomizedSelector<T>::operator() (T *array, int size, int k, Comparator cmp) {
	return select(array, 0, size-1, k, cmp);
}

template <class T>
template <class Comparator>
T RandomizedSelector<T>::select(T *array, int left, int right, int k, Comparator cmp) {
	int rpos = Random::instance().uniform(left, right+1);
	T key = array[rpos];
	array[rpos] = array[left];
	array[left] = key;
	int i = left, j = right;
	while(i < j) {
		while(i<j && cmp(key, array[j]) < 0) {
			--j;
		}
		if(i<j) {
			array[i] = array[j];
			++i;
		}
		while(i<j && cmp(array[i], key) < 0) {
			++i;
		}
		if(i<j)	{
			array[j] = array[i];
			--j;
		}
	}
	array[i] = key;
    if(k == i) {
		return array[i];
	} else if(k < i) {
		return select(array, left, i-1, k, cmp);
	} else {
		return select(array, i+1, right, k, cmp);
	}
}

}  //~ namespace ycg

#endif /* RANDOMIZEDSELECTOR_H */
