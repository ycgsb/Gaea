#include "DirectedGraphAdjList.h"

namespace ycg {

DirectedGraphAdjList::DirectedGraphAdjList(int numVertex, int maxNumEdge) {
    this->numVertex = numVertex;
    this->numEdge = 0;
    this->maxNumEdge = maxNumEdge;
    heads = new int[numVertex];
    for (int u = 0; u < numVertex; ++u) {
        heads[u] = NIL;
    }
    edges = new int[maxNumEdge];
    next = new int[maxNumEdge];
}

DirectedGraphAdjList::DirectedGraphAdjList(const DirectedGraphAdjList &val) {
    this->numVertex = val.numVertex;
    this->numEdge = val.numEdge;
    this->maxNumEdge = val.maxNumEdge;
    heads = new int[numVertex];
    for (int u = 0; u < numVertex; ++u) {
        heads[u] = val.heads[u];
    }
    edges = new int[maxNumEdge];
    next = new int[maxNumEdge];
    for (int i = 0; i < numEdge; ++i) {
        edges[i] = val.edges[i];
        next[i] = val.next[i];
    }

}

DirectedGraphAdjList::~DirectedGraphAdjList() {
    delete []heads;
    delete []edges;
    delete []next;
}

void DirectedGraphAdjList::insertEdge(const Edge &edge) {
    edges[numEdge] = edge.v;
    next[numEdge] = heads[edge.u];
    heads[edge.u] = numEdge;
    ++numEdge;
}

int DirectedGraphAdjList::countOutDegree(int vertex) const {
    int p = heads[vertex];
    int count = 0;
    while (p != NIL) {
        p = next[p];
        ++count;
    }
    return count;
}

DirectedGraphAdjList::EdgeIterator::EdgeIterator(const DirectedGraphAdjList *graph
    , int vertex) {
    this->graph = graph;
    ptr = graph->heads[vertex];
}

bool DirectedGraphAdjList::EdgeIterator::hasNext() {
    return ptr != NIL;
}

int DirectedGraphAdjList::EdgeIterator::next() {
    int v = graph->edges[ptr];
    ptr = graph->next[ptr];
    return v;
}

} //~ namespace ycg
