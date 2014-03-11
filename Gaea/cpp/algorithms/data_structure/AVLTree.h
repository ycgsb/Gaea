#ifndef AVLTREE_H
#define AVLTREE_H

template <class T>
class AVLTree{
public:
struct BSTNode {
    char     nHeight;
    T      dat;
    BSTNode *pLeft, *pRight;
};
private:
    struct BSTNode *pFree, *pHead, *pPool;
    inline BSTNode* CreateBSTNode();
    inline void DelBSTNode(BSTNode* pNode);
    inline char Height(BSTNode *pNode);
    inline BSTNode* SingleRotateWithLeft(BSTNode *pNode);
    inline BSTNode* SingleRotateWithRight(BSTNode *pNode);
    inline BSTNode* DoubleRotateWithLeft(BSTNode *pNode);
    inline BSTNode* DoubleRotateWithRight(BSTNode *pNode);
    inline BSTNode* AVLInsert(T nDat, BSTNode *&pNode);
    inline void Process(BSTNode *p, BSTNode *&tmp);
    inline int AVLDelete(BSTNode *&p, T x);
public:
    AVLTree();
    ~AVLTree();
    void insert(T nDat);
    T* find(T nDat);
    int remove(T x);
};


#endif // AVLTREE_H
