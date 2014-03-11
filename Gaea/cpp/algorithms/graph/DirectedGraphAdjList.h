#ifndef DIRECTEDGRAPHADJLIST_H
#define DIRECTEDGRAPHADJLIST_H

#include "Edge.h"

namespace ycg {

class DirectedGraphAdjList {
public:
    DirectedGraphAdjList(int numVertex, int maxNumEdge);
    DirectedGraphAdjList(const DirectedGraphAdjList &val);
    ~DirectedGraphAdjList();
    int numberOfVertex() const;
    int numberOfEdge() const;
    void insertEdge(const Edge &edge);
    int countOutDegree(int vertex) const;

    class EdgeIterator {
    public:
        EdgeIterator(const DirectedGraphAdjList *graph, int vertex);
        bool hasNext();
        int next();
    private:
        const DirectedGraphAdjList *graph;
        int ptr;
    };

    EdgeIterator edgeIterarorFromVertex(int vertex) const;
private:
    static const int NIL = -1;
    int numVertex;
    int numEdge;
    int maxNumEdge;
    int *heads;
    int *edges;
    int *next;
};

inline int DirectedGraphAdjList::numberOfVertex() const {
    return numVertex;
}

inline int DirectedGraphAdjList::numberOfEdge() const {
    return numEdge;
}

inline DirectedGraphAdjList::EdgeIterator DirectedGraphAdjList::
    edgeIterarorFromVertex(int vertex) const {
    return EdgeIterator(this, vertex);
}

} //~ namespace ycg

#endif // DIRECTEDGRAPHADJLIST_H
