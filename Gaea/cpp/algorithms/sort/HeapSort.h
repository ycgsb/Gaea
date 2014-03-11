#ifndef HEAPSORT_H_
#define HEAPSORT_H_

namespace ycg {

template <class Type>
class HeapSort {
public:
    void operator() (Type *a, int n);
private:
    void buildMaxHeap(Type *a, int n);
    void maxHeapify(Type *a, int n, int i);
    void exchange(Type &a, Type &b);
};

template <class Type>
void HeapSort<Type>::operator () (Type* a, int n) {
    buildMaxHeap(a, n);
	for (int i = n - 1; i > 0; --i) {
        exchange(a[0], a[i]);
        maxHeapify(a, i, 0);
	}
}

template <class Type>
void HeapSort<Type>::buildMaxHeap(Type *a, int n) {
    for (int i = ((n-1)>>1); i >= 0; --i) {
        maxHeapify(a, n, i);
    }
}

template<class Type>
void HeapSort<Type>::maxHeapify(Type *a, int n, int i) {
	int j = (i << 1) + 1;
    Type key = a[i];
    while (j < n) {
        if (j + 1 < n && a[j] < a[j+1])
			j++;
        if (a[j] < key)
			break;
        a[i] = a[j];
		i = j;
		j = (i << 1) + 1;
	}
    a[i] = key;
}

template <class Type>
inline void HeapSort<Type>::exchange(Type &a, Type &b) {
    Type temp = a;
    a = b;
    b = temp;
}

} //~ namespace ycg


#endif /* HEAPSORT_H_ */
