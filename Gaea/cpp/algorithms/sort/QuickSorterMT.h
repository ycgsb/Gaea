#ifndef QUICKSORTERMT_H
#define QUICKSORTERMT_H

#include "QuickSorter.h"
#include <thread>

namespace ycg {

class QuickSorterMT : public QuickSorter {
public:
	template <class T>
    void operator() (T *array, int size);
    template <class T, class Comparator>
    void operator() (T *array, int size, Comparator cmp);
protected:
    template <class T>
    void quickSort(T *array, int left, int right);
    template <class T, class Comparator>
    void quickSort(T *array, int left, int right, Comparator cmp);
private:
    static const int NUM_THREAD = 32;
    int _MTThresholdSize;
};

template <class T>
void QuickSorterMT::operator () (T *array, int size) {
	_MTThresholdSize = size / NUM_THREAD;
	quickSort(array, 0, size - 1);
}

template <class T, class Comparator>
void QuickSorterMT::operator () (T *array, int size, Comparator cmp) {
	_MTThresholdSize = size / NUM_THREAD;
	quickSort(array, 0, size - 1, cmp);
}

template <class T>
void QuickSorterMT::quickSort(T *array, int left, int right) {
    if(right - left < MIN_SEG) {
    	insertionSort(array, left, right);
    	return;
    }
    exchange(array[(left+right)/2], array[left+1]);
    compareExchange(array[left], array[left+1]);
    compareExchange(array[left], array[right]);
    compareExchange(array[left+1], array[right]);
    int mid = partition(array, left+1, right-1);
    if (right - left > _MTThresholdSize) {
    	std::thread th1([=](T *array, int left, int right){ quickSort(array, left, right); },
    			array, left, mid-1);
    	std::thread th2([=](T *array, int left, int right){ quickSort(array, left, right); },
    			array, mid + 1, right);
    	th1.join();
    	th2.join();
    } else {
    	quickSort(array, left, mid-1);
    	quickSort(array, mid+1, right);
    }
}

template <class T, class Comparator>
void QuickSorterMT::quickSort(T *array, int left, int right, Comparator cmp) {
    if(right - left < MIN_SEG) {
    	insertionSort(array, left, right, cmp);
    	return;
    }
    exchange(array[(left+right)/2], array[left+1]);
    compareExchange(array[left], array[left+1], cmp);
    compareExchange(array[left], array[right], cmp);
    compareExchange(array[left+1], array[right], cmp);
    int mid = partition(array, left+1, right-1, cmp);
    if (right - left > _MTThresholdSize) {
    	std::thread th1([=](T *array, int left, int right, Comparator cmp){
    		quickSort(array, left, right, cmp);}, array, left, mid-1, cmp);
    	std::thread th2([=](T *array, int left, int right, Comparator cmp){
    		quickSort(array, left, right, cmp);}, array, mid + 1, right, cmp);
    	th1.join();
    	th2.join();
    } else {
    	quickSort(array, left, mid-1, cmp);
    	quickSort(array, mid+1, right, cmp);
    }
}

} //~ namespace ycg

#endif // QUICKSORTERMT_H
