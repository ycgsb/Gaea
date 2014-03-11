#include "Stack.h"

namespace ycg {

template <class Type>
Stack<Type>::Stack(int capacity) {
    this->capacity = capacity;
    elems = new Type[capacity];
    top = 0;
}

template <class Type>
Stack<Type>::~Stack() {
    delete []elems;
}

template <class Type>
void Stack<Type>::expandCapacity() {
    Type* elems_new = new Type[2 * capacity];
    for(int i = 0; i < capacity; ++i)
        elems_new[i] = elems[i];
    capacity *= 2;
    delete []elems;
    elems = elems_new;
}

} //~ namespace ycg

