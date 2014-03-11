#include "ChainedHashTable.h"

namespace ycg {

template <class HashElem, class HashFunction>
ChainedHashTable<HashElem, HashFunction>::ChainedHashTable(int tableSize, int maxElements) {
    table = new int[tableSize];
    data = new HashElem[maxElements];
    next = new int[maxElements];
    index = 0;
    for (int i = 0; i < tableSize; ++i) {
        table[i] = -1;
    }
}

template <class HashElem, class HashFunction>
ChainedHashTable<HashElem, HashFunction>::~ChainedHashTable() {
    delete []table;
    delete []data;
    delete []next;
}

template <class HashElem, class HashFunction>
HashElem* ChainedHashTable<HashElem, HashFunction>::search(const HashElem &elem) {
    int p = table[hash(elem)];
    while(p != -1) {
        if(elem == data[p]) {
            return &data[p];
        }
        p = next[p];
    }
    return 0;
}

// 假设要插入的元素没有在表中
template <class HashElem, class HashFunction>
void ChainedHashTable<HashElem, HashFunction>::insert(const HashElem &elem) {
    int h = hash(elem);
    data[index] = elem;
    next[index] = table[h];
    table[h] = index;
    index++;
}

} //~ namespace ycg
