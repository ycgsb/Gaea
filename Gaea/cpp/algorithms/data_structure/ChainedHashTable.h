#ifndef CHAINEDHASHTABLE_H
#define CHAINEDHASHTABLE_H

namespace ycg {

template <class HashElem, class HashFunction>
class ChainedHashTable {
public:
    ChainedHashTable(int tableSize, int maxElements);
    ~ChainedHashTable();
    HashElem* search(const HashElem &elem);
    void insert(const HashElem &elem);
private:
    int *table, *next;
    HashElem *data;
    int index;
    HashFunction hash;
};

} //~ namespace ycg

#endif // CHAINEDHASHTABLE_H
