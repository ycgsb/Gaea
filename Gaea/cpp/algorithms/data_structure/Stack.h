#ifndef STACK_H
#define STACK_H

namespace ycg {

template <class Type>
class Stack {
public:
    Stack(int capacity = DEFAULT_CAPACITY);
    ~Stack();
    bool isEmpty();
    void push(const Type &val);
    Type pop();
    Type getTopElem();
private:
    void expandCapacity();
private:
    static const int DEFAULT_CAPACITY = 1024 / sizeof(Type);
    Type* elems;
    int top;
    int capacity;
};

template <class Type>
inline bool Stack<Type>::isEmpty() {
    return (top == 0);
}

template <class Type>
inline void Stack<Type>::push(const Type &val) {
    if (top == capacity)
        expandCapacity();
    elems[top] = val;
    top++;
}

template <class Type>
inline Type Stack<Type>::pop() {
    --top;
    return elems[top];
}

template <class Type>
inline Type Stack<Type>::getTopElem() {
    return elems[top - 1];
}

} //~ namespace ycg











#endif // STACK_H
