#include "KNN.h"
#include "../../algorithms/sort/QuickSorter.h"
namespace ycg {

KNN::KNN(int k) {
    this->numNeighbor = k;
    this->trainingData = nullptr;
    this->neighbors = new MaxBinaryHeap<Pair<double, int>>(k);
    this->votes = new int[k];
}

KNN::~KNN() {
    delete neighbors;
    delete []votes;
}

void KNN::train(const DatasetClassification *trainingData) {
    assert(trainingData->samples() >= numNeighbor);
    this->trainingData = trainingData;
}

int KNN::predict(const Vector &feature) {
    assert(trainingData != nullptr);
    selectNearestNeighbor(feature);
    int result = voteBetweenNearestNeighbor();
    return result;
}

void KNN::selectNearestNeighbor(const Vector &feature) {
    neighbors->clear();
    for (int i = 0; i < numNeighbor; ++i) {
        neighbors->add(Pair<double, int>(Vector::distanceL2(feature, trainingData->feature(i)), i));
    }
    for (int i = 0; i < trainingData->samples(); ++i) {
    	Pair<double, int> rec(Vector::distanceL2(feature, trainingData->feature(i)), i);
        if (rec < neighbors->max()) {
            neighbors->modify(0, rec);
        }
    }
}

int KNN::voteBetweenNearestNeighbor() {
	int i = 0;
    for(Pair<double, int>* iter = neighbors->begin(); iter != neighbors->end(); ++iter) {
        votes[i++] = trainingData->label(iter->second());
    }
    QuickSorter sort;
    sort(votes, numNeighbor);
    int most = 0, result = 0;
    for (int i = 0; i < numNeighbor; ++i) {
        int freq = 1;
        while(i + 1 < numNeighbor && votes[i+1] == votes[i]) {
        	++i;
        	++freq;
        }
        if (freq > most) {
            most = freq;
            result = votes[i];
        }
    }
    return result;
}

}  //~ namespace ycg
