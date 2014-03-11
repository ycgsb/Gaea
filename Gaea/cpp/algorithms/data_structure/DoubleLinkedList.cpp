#include "DoubleLinkedList.h"

//DoubleLinkedList::DoubleLinkedList()
//{
//}


//typedef struct DLList{
//elemType e;
//DLList * prior;
//DLList * next;
//}DLList;

//STATUS InitDLList(DLList * h)
//{
//if (h=(DLList *)malloc(sizeof(DLList)))
//{
//h->prior=h;
//h->next=h;
//return SUCCESS;
//}
//printf("failed to initial head pointer\n");
//return FAILED;
//}

//STATUS AddDLListNode(DLList * h,elemType e)
//{
//DLList * node,* p;
//if (h->next==h)
//{
//if (node=(DLList *)malloc(sizeof(DLList)))
//{
//h->next=node;
//node->prior=h;
//node->next=h;
//node->e=e;
//return SUCCESS;
//}
//printf("failed to add new element\n");
//return FAILED;
//}
//p=h;
//while(p->next!=h)
//{
//p=p->next;
//}
//if (node=(DLList *)malloc(sizeof(DLList)))
//{
//node->prior=p;
//node->next=h;
//node->prior->next=node;
//node->e=e;
//return SUCCESS;
//}
//printf("failed add new element\n");
//return FAILED;
//}


//STATUS InsertDLList(DLList * h,elemType e,int index)/*insert element after index*/
//{
//int i;
//i=1;
//DLList * p,* node;
//p=h;
//while(i!=index)
//{
//p=p->next;
//i++;
//}
//if (node=(DLList *)malloc(sizeof(DLList)))
//{
//p->next->prior=node;
//node->next=p->next;
//p->next=node;
//node->prior=p;
//return SUCCESS;
//}
//printf("failed to insert new element\n");
//return FAILED;
//}
