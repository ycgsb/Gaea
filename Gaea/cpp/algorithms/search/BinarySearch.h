#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

namespace ycg {

class BinarySearch {
public:
	template <class KeyT, class ElemT>
	int operator() (const KeyT& key, const ElemT *array, int size);
	template <class KeyT, class ElemT, class Comparator>
    int operator() (const KeyT& key, const ElemT *array, int size, Comparator cmp);
};

template <class KeyT, class ElemT>
int BinarySearch::operator() (const KeyT& key, const ElemT *array, int size) {
	int left = 0;
    int right = size - 1;
    while(left <= right) {
        int mid = (left + right) / 2; //attention: overflow
        if(array[mid] == key) {
            return mid;
        } else if(array[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
   }
   return -1;
}

template <class KeyT, class ElemT, class Comparator>
int BinarySearch::operator() (const KeyT& key, const ElemT *array, int size, Comparator cmp) {
    int left = 0;
    int right = size - 1;
    while(left <= right) {
        int mid = (left + right) / 2; //attention: overflow
        if(cmp(key, array[mid]) == 0) {
            return mid;
        } else if(cmp(key, array[mid]) > 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
   }
   return -1;
}

} //~ namespace ycg

#endif // BINARYSEARCH_H
