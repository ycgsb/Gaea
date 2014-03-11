#ifndef OPENADDRESSINGHASHTABLE_H
#define OPENADDRESSINGHASHTABLE_H

namespace ycg {

template <class HashElem, class HashFunction>
class OpenAddressingHashTable
{
public:
    OpenAddressingHashTable(int tableSize);
    ~OpenAddressingHashTable();
    HashElem* search(const HashElem &elem);
    void insert(const HashElem &elem);
private:
    int *table;
    int tableSize;
    HashElem *data;
    int index;
    HashFunction hash;
};


} //~ namespace ycg

#endif // OPENADDRESSINGHASHTABLE_H
