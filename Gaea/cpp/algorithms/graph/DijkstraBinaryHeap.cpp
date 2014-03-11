#include "DijkstraBinaryHeap.h"

namespace ycg {

const double DijkstraBinaryHeap::INF = 1e300;
DijkstraBinaryHeap::DijkstraBinaryHeap(const DirectedWeightedGraphAdjList *graph) {
    this->graph = graph;
    int numVertex = graph->numberOfVertex();
    distance = new HeapHandle<double>[numVertex];
    set = new bool[numVertex];
}

DijkstraBinaryHeap::~DijkstraBinaryHeap() {
    delete []distance;
    delete []set;
}

void DijkstraBinaryHeap::computeShortestDistance(int sourceVertex) {
    int numVertex = graph->numberOfVertex();
    for (int i = 0; i < numVertex; ++i) {
        distance[i].object = INF;
        distance[i].tag = i;
        set[i] = false;
    }
    distance[sourceVertex].object = 0;
    MinPriorityQueueBinaryHeap<double> queue(distance, numVertex);
    while (!queue.isEmpty()) {
        int u = queue.extractMin()->tag;
        set[u] = true;
        DirectedWeightedGraphAdjList::EdgeIterator itr = graph->edgeIterarorFromVertex(u);
        while (itr.hasNext()) {
            WeightedEdge edge = itr.next();
            int v = edge.v;
            double weight = edge.weight;
            if (!set[v] && distance[u].object + weight < distance[v].object) {
                queue.decrease(&distance[v], distance[u].object + weight);
            }
        }
    }
}

} //~ namespace ycg
