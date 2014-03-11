#ifndef DIRECTEDGRAPHADJMATRIX_H
#define DIRECTEDGRAPHADJMATRIX_H

#include "Edge.h"

namespace ycg {

/*
 * Representation of Graph:
 * Directed, unweighted, at most one edge between two vertex
 * vertex is numbered from 0 to N-1
 */
class DirectedGraphAdjMatrix {
public:
    DirectedGraphAdjMatrix(int numVertex);
    DirectedGraphAdjMatrix(const DirectedGraphAdjMatrix &val);
    ~DirectedGraphAdjMatrix();
    int numberOfVertex() const;
    void insertEdge(const Edge &edge);
    void removeEdge(const Edge &edge);
    void removeEdges(int v);
    bool existEdge(const Edge &edge) const;

    const bool* operator [](int i) const;
    bool* operator [](int i);
private:
    int numVertex;
    bool *graph;
};

inline int DirectedGraphAdjMatrix::numberOfVertex() const {
    return numVertex;
}

inline void DirectedGraphAdjMatrix::insertEdge(const Edge &edge) {
    graph[edge.u * numVertex + edge.v] = true;
}

inline void DirectedGraphAdjMatrix::removeEdge(const Edge &edge) {
    graph[edge.u * numVertex + edge.v] = false;
}

inline bool DirectedGraphAdjMatrix::existEdge(const Edge &edge) const {
    return graph[edge.u * numVertex + edge.v];
}

inline const bool* DirectedGraphAdjMatrix::operator [](int i) const {
    return graph + i * numVertex;
}

inline bool* DirectedGraphAdjMatrix::operator [](int i) {
    return graph + i * numVertex;
}

} //~ namespace ycg

#endif // DIRECTEDGRAPHADJMATRIX_H
