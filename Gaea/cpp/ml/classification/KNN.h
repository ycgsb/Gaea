#ifndef KNN_H
#define KNN_H

#include "AbstractClassifier.h"
#include "../../algorithms/data_structure/BinaryHeap.h"
#include "../../util/Pair.h"

namespace ycg {

class KNN : public AbstractClassifier {
public:
    KNN(int k);
    virtual ~KNN();
    virtual void train(const DatasetClassification *trainingData);
    virtual int predict(const Vector& feature);
private:
    void selectNearestNeighbor(const Vector& feature);
    int voteBetweenNearestNeighbor();
private:
    int numNeighbor;
    const DatasetClassification *trainingData;
    MaxBinaryHeap<Pair<double, int>> *neighbors;
    int *votes;
};

} //~ namespace ycg


#endif /* KNN_H */
