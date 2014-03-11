#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include "DirectedGraphAdjMatrix.h"
#include "../data_structure/Queue.h"

namespace ycg {

class BreadthFirstSearch {
public:
    BreadthFirstSearch(const DirectedGraphAdjMatrix* graph, int source);
    ~BreadthFirstSearch();
    void search();
    int queryShortestDistance(int v);
    bool queryReachable(int v);
    void printShortestPath(int v);
private:
    static const int OO = 1000000000;
    static const int NIL = -1;
    enum COLOR {
        WHITE, BLACK, GRAY
    };
    const DirectedGraphAdjMatrix *graph;
    int sourceVertex;
    int *color;
    int *distance;
    int *prev;
};

} //~ namespace ycg

#endif // BREADTHFIRSTSEARCH_H
