#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <cassert>

namespace ycg {

template <class T>
class BinaryHeap {
public:
    BinaryHeap(int capacity);
    BinaryHeap(int capacity, const T *array, int size);
    virtual ~BinaryHeap();
    void add(const T& elem);
    T extract();
    const T& top() const;
    int size() const;
    int capacity() const;
    void clear();
    void modify(int i, const T &elem);
    T* begin();
    T* end();
protected:
    virtual void shiftUp(int i) = 0;
    virtual void shiftDown(int i) = 0;
protected:
    T* heap;
    int _size;
    int _capacity;
};

template <class T>
class MaxBinaryHeap : public BinaryHeap<T> {
public:
    MaxBinaryHeap(int capacity);
    MaxBinaryHeap(int capacity, const T *array, int size);
    const T& max() const;
protected:
    void shiftUp(int i);
    void shiftDown(int i);
};

template <class T>
class MinBinaryHeap : public BinaryHeap<T> {
public:
    MinBinaryHeap(int capacity);
    MinBinaryHeap(int capacity, const T *array, int size);
    const T& min() const;
protected:
    void shiftUp(int i);
    void shiftDown(int i);
};

template <class T>
BinaryHeap<T>::BinaryHeap(int capacity) {
	assert(capacity > 0);
	_capacity = capacity;
	_size = 0;
	heap = new T[capacity];
}

template <class T>
BinaryHeap<T>::BinaryHeap(int capacity, const T *array, int size) {
	assert(capacity > 0);
	assert(array != nullptr);
	assert(size >= 0 && size <= capacity);
	_capacity = capacity;
	_size = size;
	heap = new T[capacity];
	for (int i = 0; i < size; ++i) {
		heap[i] = array[i];
	}
}

template <class T>
BinaryHeap<T>::~BinaryHeap() {
    delete []heap;
}

template <class T>
inline void BinaryHeap<T>::add(const T &elem) {
    assert(size() + 1 <= capacity());
	heap[_size] = elem;
    shiftUp(_size);
    ++_size;
}

template <class T>
inline T BinaryHeap<T>::extract() {
    T top = heap[0];
    heap[0] = heap[--_size];
    shiftDown(0);
    return top;
}

template <class T>
inline const T& BinaryHeap<T>::top() const {
    assert(_size >= 1);
    return heap[0];
}

template <class T>
inline int BinaryHeap<T>::size() const {
	return _size;
}

template <class T>
inline int BinaryHeap<T>::capacity() const {
	return _capacity;
}

template <class T>
inline void BinaryHeap<T>::clear() {
    _size = 0;
}

template <class T>
void BinaryHeap<T>::modify(int i, const T &elem) {
    heap[i] = elem;
    shiftUp(i);
    shiftDown(i);
}

template <class T>
inline T* BinaryHeap<T>::begin() {
	return heap;
}

template <class T>
inline T* BinaryHeap<T>::end() {
	return heap + _size;
}

template <class T>
MaxBinaryHeap<T>::MaxBinaryHeap(int capacity) :
	BinaryHeap(capacity) { }

template <class T>
MaxBinaryHeap<T>::MaxBinaryHeap(int capacity, const T *array, int size) :
	BinaryHeap(capacity, array, size) {
	for (int i = size / 2 - 1; i >= 0; --i) {
		shiftDown(i);
	}
}

template <class T>
inline const T& MaxBinaryHeap<T>::max() const {
    return top();
}

template <class T>
void MaxBinaryHeap<T>::shiftUp(int i) {
    int j = (i-1)>>1;
    T key = heap[i];
    while(i > 0 && heap[j] < key) {
        heap[i] = heap[j];
        i = j;
        j = (i - 1) >> 1;
    }
    heap[i] = key;
}

template <class T>
void MaxBinaryHeap<T>::shiftDown(int i) {
    int j = (i << 1) + 1;
    T key = heap[i];
    while (j < _size) {
        if (j + 1 < _size && heap[j] < heap[j+1])
            j++;
        if (key < heap[j]) {
            heap[i] = heap[j];
            i = j;
            j = (i << 1) + 1;
        } else {
            break;
        }
    }
    heap[i] = key;
}

template <class T>
MinBinaryHeap<T>::MinBinaryHeap(int capacity) :
 	BinaryHeap(capacity) { }

template <class T>
MinBinaryHeap<T>::MinBinaryHeap(int capacity, const T *array, int size) :
	BinaryHeap(capacity, array, size) {
	for (int i = size / 2 - 1; i >= 0; --i) {
		shiftDown(i);
	}
}

template <class T>
inline const T& MinBinaryHeap<T>::min() const {
    return top();
}

template <class T>
void MinBinaryHeap<T>::shiftUp(int i) {
    int j = (i - 1) >> 1;
    T key = heap[i];
    while(i > 0 && key < heap[j]) {
        heap[i] = heap[j];
        i = j;
        j = (i - 1) >> 1;
    }
    heap[i] = key;
}

template <class T>
void MinBinaryHeap<T>::shiftDown(int i) {
    int j = (i << 1) + 1;
    T key = heap[i];
    while (j < _size) {
        if (j + 1 < _size && heap[j+1] < heap[j])
            j++;
        if (heap[j] < key) {
            heap[i] = heap[j];
            i = j;
            j = (i << 1) + 1;
        } else {
            break;
        }
    }
    heap[i] = key;
}

} //~ namespace ycg


#endif /* BINARYHEAP_H */
