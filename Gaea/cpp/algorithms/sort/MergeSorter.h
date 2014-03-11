#ifndef MERGESORTER_H
#define MERGESORTER_H

namespace ycg {

class MergeSorter {
public:
	template <class T>
    void operator() (T *array, int size);
	template <class T, class Comparator>
	void operator() (T *array, int size, Comparator cmp);
private:
	template <class T>
    void mergeSort(T *array, T *temp, int left, int right);
	template <class T, class Comparator>
	void mergeSort(T *array, T *temp, int left, int right, Comparator cmp);
	template <class T>
	void merge(T *array, T *temp, int left, int mid, int right);
	template <class T, class Comparator>
	void merge(T *array, T *temp, int left, int mid, int right, Comparator cmp);
    template <class T>
    void insertionSort(T *array, int left, int right);
    template <class T, class Comparator>
    void insertionSort(T *array, int left, int right, Comparator cmp);
private:
	static const int MIN_SEG = 16;
};

template <class T>
void MergeSorter::operator () (T *array, int size) {
    T *temp = new T[size];
    mergeSort(array, temp, 0, size - 1);
    delete []temp;
}

template <class T, class Comparator>
void MergeSorter::operator () (T *array, int size, Comparator cmp) {
    T *temp = new T[size];
    mergeSort(array, temp, 0, size - 1, cmp);
    delete []temp;
}

template <class T>
void MergeSorter::mergeSort(T *array, T *temp, int left, int right) {
    if (right - left < MIN_SEG) {
    	insertionSort(array, left, right);
    	return;
    }
    int mid = (left + right) / 2;
    mergeSort(array, temp, left, mid);
    mergeSort(array, temp, mid + 1, right);
    merge(array, temp, left, mid, right);
}

template <class T, class Comparator>
void MergeSorter::mergeSort(T *array, T *temp, int left, int right, Comparator cmp) {
	if (right - left < MIN_SEG) {
		insertionSort(array, left, right, cmp);
		return;
	}
	int mid = (left + right) / 2;
	mergeSort(array, temp, left, mid, cmp);
	mergeSort(array, temp, mid + 1, right, cmp);
	merge(array, temp, left, mid, right, cmp);
}

template <class T>
void MergeSorter::merge(T *array, T *temp, int left, int mid, int right) {
    for (int i = left; i <= right; ++i) {
    	temp[i] = array[i];
    }
    int i = left, j = mid+1, k = left;
    while (i <= mid && j <= right) {
        if (temp[i] < temp[j]) {
            array[k++] = temp[i++];
        } else {
            array[k++] = temp[j++];
        }
    }
    while (i <= mid) {
        array[k++] = temp[i++];
    }
    while (j <= right) {
        array[k++] = temp[j++];
    }
}

template <class T, class Comparator>
void MergeSorter::merge(T *array, T *temp, int left, int mid, int right, Comparator cmp) {
	for (int i = left; i <= right; ++i) {
		temp[i] = array[i];
	}
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		if (cmp(temp[i], temp[j]) < 0) {
			array[k++] = temp[i++];
		} else {
			array[k++] = temp[j++];
		}
	}
	while (i <= mid) {
		array[k++] = temp[i++];
	}
	while (j <= right) {
		array[k++] = temp[j++];
	}
}

template <class T>
void MergeSorter::insertionSort(T *array, int left, int right) {
    for(int j = left + 1; j <= right; ++j) {
        int i = j - 1;
        T key = array[j];
        while(i >= left && key < array[i]) {
            array[i+1] = array[i];
            --i;
        }
        array[i+1] = key;
    }
}

template <class T, class Comparator>
void MergeSorter::insertionSort(T *array, int left, int right, Comparator cmp) {
    for(int j = left + 1; j <= right; ++j) {
        int i = j - 1;
        T key = array[j];
        while(i >= left && cmp(key, array[i]) < 0) {
            array[i+1] = array[i];
            --i;
        }
        array[i+1] = key;
    }
}

} //~ namespace ycg

#endif // MERGESORT_H
