#ifndef QUEUE_H
#define QUEUE_H

namespace ycg {

template <class Type>
class Queue {
public:
    Queue(int capacity = DEFAULT_CAPACITY);
    bool isEmpty() const;
    void enqueue(const Type &elem);
    Type dequeue();
private:
    bool isFull() const;
private:
    static const int DEFAULT_CAPACITY = 1024 / sizeof(Type);
    Type* queue;
    int capacity;
    int head, tail;
};

template <class Type>
Queue<Type>::Queue(int capacity) {
    queue = new Type[capacity];
    this->capacity = capacity;
    head = tail = 0;
}

template <class Type>
inline bool Queue<Type>::isEmpty() const {
    return (head==tail);
}

template <class Type>
inline void Queue<Type>::enqueue(const Type &elem) {
    queue[tail] = elem;
    ++tail;
    if(tail == capacity)
        tail = 0;
}

template <class Type>
inline Type Queue<Type>::dequeue() {
    const Type& elem = queue[head];
    ++head;
    if(head == capacity)
        head = 0;
    return elem;
}

} //~ namespace ycg


#endif // QUEUE_H
