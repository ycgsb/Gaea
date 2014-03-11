#ifndef WEIGHTEDGRAPHADJMATRIX_H
#define WEIGHTEDGRAPHADJMATRIX_H

namespace ycg {

/*
 * Representation of Graph:
 * Undirected, weighted, at most one edge between two vertex
 * vertex is numbered from 0 to N-1
 */
class WeightedGraphAdjMatrix {
public:
	WeightedGraphAdjMatrix(int numVertex);
    WeightedGraphAdjMatrix(int numVertex, double initWeight);
    ~WeightedGraphAdjMatrix();
    int numberOfVertex() const;
    void insertEdge(int v1, int v2, double weight);
    const double* operator [](int i) const;
    double* operator [](int i);
private:
    int numVertex;
    double *graph;
};

inline int WeightedGraphAdjMatrix::numberOfVertex() const {
    return numVertex;
}

inline void WeightedGraphAdjMatrix::insertEdge(int v1, int v2, double weight) {
    graph[v1 * numVertex + v2] = weight;
    graph[v2 * numVertex + v1] = weight;
}

inline const double* WeightedGraphAdjMatrix::operator [](int i) const {
    return graph + i * numVertex;
}

inline double* WeightedGraphAdjMatrix::operator [](int i) {
    return graph + i * numVertex;
}

} //~ namespace ycg

#endif // WEIGHTEDGRAPHADJMATRIX_H
