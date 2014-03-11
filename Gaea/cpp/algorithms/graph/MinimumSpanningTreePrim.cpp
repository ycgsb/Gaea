#include "MinimumSpanningTreePrim.h"

namespace ycg {

MinimumSpanningTreePrim::MinimumSpanningTreePrim(const WeightedGraphAdjMatrix *graph) {
    this->graph = graph;
    int nVertex = graph->numberOfVertex();
    flag = new bool[nVertex];
    key = new double[nVertex];
    prev = new int[nVertex];
}

MinimumSpanningTreePrim::~MinimumSpanningTreePrim() {
    delete []flag;
    delete []key;
    delete []prev;
}

void MinimumSpanningTreePrim::compute() {
    const double OO = 1e200;
    const WeightedGraphAdjMatrix &graph = *(this->graph);

    int src = 0;
    for (int i = 0; i < graph.numberOfVertex(); ++i) {
        flag[i] = false;
        key[i] = graph[src][i];
        prev[i] = src;
    }
    flag[src] = true;
    key[src] = 0;
    totalWeight = 0.0;
    for (int i = 1; i < graph.numberOfVertex(); ++i) {
        double min = OO;
        int k;
        for (int j = 0; j < graph.numberOfVertex(); ++j) {
            if(!flag[j] && min > key[j]) {
                min = key[j];
                k = j;
            }
        }
        flag[k] = true;
        key[k] = min;
        totalWeight += min;
        for (int j = 0; j < graph.numberOfVertex(); ++j) {
            if(!flag[j] && key[j] > graph[k][j]) {
                key[j] = graph[k][j];
                prev[j] = k;
            }
        }
    }
}

} //~ namespace ycg
