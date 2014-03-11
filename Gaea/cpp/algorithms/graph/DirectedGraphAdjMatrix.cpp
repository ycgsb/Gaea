#include "DirectedGraphAdjMatrix.h"

namespace ycg {

DirectedGraphAdjMatrix::DirectedGraphAdjMatrix(int numVertex) {
    this->numVertex = numVertex;
    int size = numVertex * numVertex;
    graph = new bool[size];
    for (int i = 0; i < size; ++i) {
        graph[i] = false;
    }
}

DirectedGraphAdjMatrix::DirectedGraphAdjMatrix(const DirectedGraphAdjMatrix &val) {
    numVertex = val.numVertex;
    int size = numVertex * numVertex;
    graph = new bool[size];
    for (int i = 0; i < size; ++i) {
        graph[i] = val.graph[i];
    }
}

DirectedGraphAdjMatrix::~DirectedGraphAdjMatrix() {
    delete []graph;
}

// Remove all edges connect to vertex v
void DirectedGraphAdjMatrix::removeEdges(int v) {
    for (int u = 0; u < numVertex; ++u) {
        graph[u * numVertex + v] = false;
        graph[v * numVertex + u] = false;
    }
}

} //~ namespace ycg
