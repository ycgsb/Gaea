#include "ItemBasedCFMT.h"
#include <thread>
#include <cstdio>

namespace ycg {

ItemBasedCFMT::ItemBasedCFMT(RatingMatrixStatic& rms, int similarityType, int modelType,
        int nearestK, int predictionType) :
    ItemBasedCF(rms, similarityType, modelType, nearestK, predictionType) {}

void ItemBasedCFMT::train() {
    std::thread **threads = new std::thread*[NUM_THREAD];
    for (int i = 0; i < NUM_THREAD; ++i) {
        ComputeSimMatRunner runner(this);
        threads[i] = new std::thread(runner, i);
    }
    for (int i = 0; i < NUM_THREAD; ++i) {
        threads[i]->join();
        delete threads[i];
    }
    if (modelType == MODEL_NEAREST_K) {
    	for (int i = 0; i < NUM_THREAD; ++i) {
    		ComputeNearestKRunner runner(this);
    		threads[i] = new std::thread(runner, i);
    	}
    	for (int i = 0; i < NUM_THREAD; ++i) {
    		threads[i]->join();
    		delete threads[i];
    	}
    }
    delete []threads;
}

void ItemBasedCFMT::ComputeSimMatRunner::operator () (int threadID) {
    int total = ibcf->numItem * ( ibcf->numItem - 1) / 2;
    int work = total / NUM_THREAD;
    int begin = threadID*work;
    int end = (threadID != NUM_THREAD-1)?(begin+work):total;
    for (int id = begin; id < end; ++id) {
        int x = static_cast<int>((sqrt(8.0*id+1)+1)/2);
        int y = id - x*(x-1)/2;
        ibcf->simMat[x][y] = ibcf->simMat[y][x] = ibcf->computeSim(x, y);
    }
}

void ItemBasedCFMT::ComputeNearestKRunner::operator () (int threadID) {
	int total = ibcf->numItem;
	int work = total / NUM_THREAD;
	int begin = threadID*work;
	int end = (threadID != NUM_THREAD-1)?(begin+work):total;
	for (int id = begin; id < end; ++id) {
		ibcf->computeNearestK(id);
	}
}

} //~ namespace ycg
