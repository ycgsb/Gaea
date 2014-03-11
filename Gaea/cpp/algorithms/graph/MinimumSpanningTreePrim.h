#ifndef MINIMUMSPANNINGTREEPRIM_H
#define MINIMUMSPANNINGTREEPRIM_H

#include "WeightedGraphAdjMatrix.h"

namespace ycg {

class MinimumSpanningTreePrim {
public:
    MinimumSpanningTreePrim(const WeightedGraphAdjMatrix *graph);
    ~MinimumSpanningTreePrim();
    void compute();
    double getTotalWeight() const;
private:
    const WeightedGraphAdjMatrix *graph;
    bool *flag;
    double *key;
    int *prev;
    double totalWeight;
};

inline double MinimumSpanningTreePrim::getTotalWeight() const {
    return totalWeight;
}

} //~ namespace ycg


#endif // MINIMUMSPANNINGTREEPRIM_H
