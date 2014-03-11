#include "WeightedGraphAdjMatrix.h"

namespace ycg {

WeightedGraphAdjMatrix::WeightedGraphAdjMatrix(int numVertex) {
	this->numVertex = numVertex;
	int size = numVertex * numVertex;
	graph = new double[size];
}

WeightedGraphAdjMatrix::WeightedGraphAdjMatrix(int numVertex, double initWeight) {
    this->numVertex = numVertex;
    int size = numVertex * numVertex;
    graph = new double[size];
    for (int i = 0; i < size; ++i) {
        graph[i] = initWeight;
    }
}

WeightedGraphAdjMatrix::~WeightedGraphAdjMatrix() {
    delete []graph;
}

} //~ namespace ycg
