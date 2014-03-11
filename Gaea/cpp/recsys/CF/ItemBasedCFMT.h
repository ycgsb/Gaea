#ifndef ITEMBASEDCFMT_H
#define ITEMBASEDCFMT_H

#include "ItemBasedCF.h"

namespace ycg {

class ItemBasedCFMT : public ItemBasedCF {
public:
    ItemBasedCFMT(RatingMatrixStatic& rms, int similarityType = SIM_ADJUSTED_COSINE,
                int modelType = MODEL_NEAREST_K, int nearsestK = 50,
                int predictionType = PRED_WEIGHTED_SUM);
    virtual void train();
private:
    class ComputeSimMatRunner;
    friend class ComputeSimMatRunner;
    class ComputeSimMatRunner {
    public:
        ComputeSimMatRunner(ItemBasedCFMT *ibcf) {
            this->ibcf = ibcf;
        }
        void operator() (int threadID);
    private:
        ItemBasedCFMT *ibcf;
    };
    class ComputeNearestKRunner;
    friend class ComputeNearestKRunner;
    class ComputeNearestKRunner {
    public:
    	ComputeNearestKRunner(ItemBasedCFMT *ibcf) {
    		this->ibcf = ibcf;
    	}
    	void operator() (int threadID);
    private:
    	ItemBasedCFMT *ibcf;
    };
private:
    const static int NUM_THREAD = 16;
};

} //~ namespace ycg

#endif // ITEMBASEDCFMT_H
