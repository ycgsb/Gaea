#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

namespace ycg {

template <class Type>
class DoubleLinkedList
{
public:
    DoubleLinkedList();
    Type* find(const Type& val);
    void insert(const Type& val);
    void remove(const Type& val);
};

} //~ namespace ycg


#endif // DOUBLELINKEDLIST_H
