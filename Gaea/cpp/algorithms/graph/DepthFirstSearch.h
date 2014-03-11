#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "DirectedGraphAdjMatrix.h"

namespace ycg {

class DepthFirstSearch {
public:
    DepthFirstSearch(const DirectedGraphAdjMatrix* graph);
    ~DepthFirstSearch();
    int search();
private:
    void visit(int u);
private:
    static const int NIL = -1;
    enum COLOR {
        WHITE, BLACK, GRAY
    };
    const DirectedGraphAdjMatrix *graph;
    int *color;
    int *discover;
    int *finish;
    int *prev;
    int time;
};


} //~ namespace ycg

#endif // DEPTHFIRSTSEARCH_H
