#ifndef DIRECTEDWEIGHTEDGRAPHADJLIST_H
#define DIRECTEDWEIGHTEDGRAPHADJLIST_H

#include "Edge.h"

namespace ycg {

/*
 * Representation of Graph:
 * Directed, Weighted(weight type = double), Adjacency-List
 * vertex is numbered from 0 to N-1
 */
class DirectedWeightedGraphAdjList {
public:
    DirectedWeightedGraphAdjList(int numVertex, int maxNumEdge);
    DirectedWeightedGraphAdjList(const DirectedWeightedGraphAdjList &obj);
    ~DirectedWeightedGraphAdjList();
    int numberOfVertex() const;
    int numberOfEdge() const;
    void insertEdge(const WeightedEdge &edge);

    class EdgeIterator {
    public:
        EdgeIterator(const DirectedWeightedGraphAdjList *graph, int vertex);
        bool hasNext();
        WeightedEdge next();
    private:
        const DirectedWeightedGraphAdjList *graph;
        int vertex;
        int nextPtr;
    };

    EdgeIterator edgeIterarorFromVertex(int vertex) const;
private:
    static const int NIL = -1;
    int numVertex;
    int numEdge;
    int maxNumEdge;
    int *heads;
    int *edges;
    double *weights;
    int *next;

};

inline int DirectedWeightedGraphAdjList::numberOfVertex() const {
    return numVertex;
}

inline int DirectedWeightedGraphAdjList::numberOfEdge() const {
    return numEdge;
}

inline DirectedWeightedGraphAdjList::EdgeIterator DirectedWeightedGraphAdjList::
    edgeIterarorFromVertex(int vertex) const {
    return EdgeIterator(this, vertex);
}

} //~ namespace ycg


#endif // DIRECTEDWEIGHTEDGRAPHADJLIST_H
