#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_

namespace ycg {

template <class T>
class BubbleSort {
public:
    void operator() (T *a, int n);
};

template <class T>
void BubbleSort<T>::operator ()(T *a, int n) {
	bool done = false;
    for (int i = 0; !done && i < n; ++i) {
		done = true;
        for (int j = n - 1; j > i; --j) {
            if (a[j] < a[j-1]) {
                T temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
				done = false;
			}
		}
	}
}

} //~ namespace ycg

#endif /* BUBBLESORT_H_ */
