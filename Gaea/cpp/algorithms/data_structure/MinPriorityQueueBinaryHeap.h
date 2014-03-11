#ifndef MINPRIORITYQUEUEBINARYHEAP_H
#define MINPRIORITYQUEUEBINARYHEAP_H

namespace ycg {

template <class T>
class MinPriorityQueueBinaryHeap;

template <class T>
class HeapHandle {
public:
    T object;
    int tag;
private:
    int posInHeap;
    friend class MinPriorityQueueBinaryHeap<T>;
};

template <class T>
class MinPriorityQueueBinaryHeap {
public:
//    MinPriorityQueueBinaryHeap(int maxSize);
    MinPriorityQueueBinaryHeap(HeapHandle<T> *handles, int nHandles);
    HeapHandle<T>* min() const;
    HeapHandle<T>* extractMin();
    void decrease(HeapHandle<T> *handle, const T& obj);
    bool isEmpty() const;
//    void update(const HeapHandle<T>* handle);
//    void insert(Handle *node);
private:
    void shiftDown(int i);
    void shiftUp(int i);
private:
    HeapHandle<T>** heap;
    int heapSize;
};

template <class T>
MinPriorityQueueBinaryHeap<T>::MinPriorityQueueBinaryHeap(HeapHandle<T> *handles, int nHandles) {
    heapSize = nHandles;
    heap = new HeapHandle<T>*[heapSize];
    for (int i = 0; i < nHandles; ++i) {
        heap[i] = &handles[i];
        heap[i]->posInHeap = i;
    }
    for (int i = ((heapSize-1)>>1); i >= 0; --i) {
        shiftDown(i);
    }
}

template <class T>
inline HeapHandle<T>* MinPriorityQueueBinaryHeap<T>::min() const {
    return heap[0];
}

template <class T>
HeapHandle<T>* MinPriorityQueueBinaryHeap<T>::extractMin() {
    HeapHandle<T> *min = heap[0];
    --heapSize;
    heap[0] = heap[heapSize];
    heap[0]->posInHeap = 0;
    shiftDown(0);
    return min;
}

template <class T>
void MinPriorityQueueBinaryHeap<T>::decrease(HeapHandle<T> *handle, const T &obj) {
    handle->object = obj;
    shiftUp(handle->posInHeap);
}

template <class T>
bool MinPriorityQueueBinaryHeap<T>::isEmpty() const {
    return heapSize==0;
}

template <class T>
void MinPriorityQueueBinaryHeap<T>::shiftDown(int i) {
    int j = (i << 1) + 1;
    HeapHandle<T> *key = heap[i];
    while (j < heapSize) {
        if (j + 1 < heapSize && heap[j+1]->object < heap[j]->object)
            j++;
        if (heap[j]->object < key->object) {
            heap[i] = heap[j];
            heap[i]->posInHeap = i;
            i = j;
            j = (i << 1) + 1;
        } else {
            break;
        }
    }
    heap[i] = key;
    heap[i]->posInHeap = i;
}

template <class T>
void MinPriorityQueueBinaryHeap<T>::shiftUp(int i) {
    int j = (i-1)>>1;
    HeapHandle<T> *key = heap[i];
    while(i > 0 && key->object < heap[j]->object) {
        heap[i] = heap[j];
        heap[i]->posInHeap = i;
        i = j;
        j >>= 1;
    }
    heap[i] = key;
    heap[i]->posInHeap = i;
}

} //~ namespace ycg
#endif // MINPRIORITYQUEUEBINARYHEAP_H
