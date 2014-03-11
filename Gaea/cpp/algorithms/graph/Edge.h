#ifndef EDGE_H
#define EDGE_H

namespace ycg {

class Edge {
public:
    Edge(int u, int v) {
        this->u = u;
        this->v = v;
    }
public:
    int u, v;
};

class WeightedEdge {
public:
    WeightedEdge(int u, int v, double weight) {
        this->u = u;
        this->v = v;
        this->weight = weight;
    }
public:
    int u, v;
    double weight;
};

} //~ namespace ycg

#endif // EDGE_H
