#include "DirectedWeightedGraphAdjList.h"

namespace ycg {
DirectedWeightedGraphAdjList::DirectedWeightedGraphAdjList(int numVertex, int maxNumEdge) {
    this->numVertex = numVertex;
    this->numEdge = 0;
    this->maxNumEdge = maxNumEdge;
    heads = new int[numVertex];
    for (int u = 0; u < numVertex; ++u) {
        heads[u] = NIL;
    }
    edges = new int[maxNumEdge];
    weights = new double[maxNumEdge];
    next = new int[maxNumEdge];
}

DirectedWeightedGraphAdjList::DirectedWeightedGraphAdjList(const DirectedWeightedGraphAdjList &obj) {
    this->numVertex = obj.numVertex;
    this->numEdge = obj.numEdge;
    this->maxNumEdge = obj.maxNumEdge;
    heads = new int[numVertex];
    for (int u = 0; u < numVertex; ++u) {
        heads[u] = obj.heads[u];
    }
    edges = new int[maxNumEdge];
    weights = new double[maxNumEdge];
    next = new int[maxNumEdge];
    for (int i = 0; i < numEdge; ++i) {
        edges[i] = obj.edges[i];
        weights[i] = obj.weights[i];
        next[i] = obj.next[i];
    }
}

DirectedWeightedGraphAdjList::~DirectedWeightedGraphAdjList() {
    delete []heads;
    delete []edges;
    delete []weights;
    delete []next;
}

void DirectedWeightedGraphAdjList::insertEdge(const WeightedEdge &edge) {
    edges[numEdge] = edge.v;
    weights[numEdge] = edge.weight;
    next[numEdge] = heads[edge.u];
    heads[edge.u] = numEdge;
    ++numEdge;
}

DirectedWeightedGraphAdjList::EdgeIterator::EdgeIterator(const DirectedWeightedGraphAdjList *graph
    , int vertex) {
    this->graph = graph;
    this->vertex = vertex;
    this->nextPtr = graph->heads[vertex];
}

bool DirectedWeightedGraphAdjList::EdgeIterator::hasNext() {
    return nextPtr != NIL;
}

WeightedEdge DirectedWeightedGraphAdjList::EdgeIterator::next() {
    WeightedEdge edge(vertex, graph->edges[nextPtr], graph->weights[nextPtr]);
    nextPtr = graph->next[nextPtr];
    return edge;
}

} //~ namespace ycg
