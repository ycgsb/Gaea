#ifndef DIJKSTRABINARYHEAP_H
#define DIJKSTRABINARYHEAP_H

#include "DirectedWeightedGraphAdjList.h"
#include "../data_structure/MinPriorityQueueBinaryHeap.h"

namespace ycg {

/**
 * Single-Source Shortest-Paths Problem
 * Dijkstra algorithm, use binary heap as priority queue
 * O((V+E)lgV)
 */

class DijkstraBinaryHeap {
public:
    DijkstraBinaryHeap(const DirectedWeightedGraphAdjList* graph);
    ~DijkstraBinaryHeap();
    void computeShortestDistance(int sourceVertex);
    double shortestDistance(int v);
public:
    static const double INF;
private:
    const DirectedWeightedGraphAdjList* graph;
    HeapHandle<double> *distance;
    bool *set;
};

inline double DijkstraBinaryHeap::shortestDistance(int v) {
    return distance[v].object;
}

} //~ namespace ycg

#endif // DIJKSTRABINARYHEAP_H
