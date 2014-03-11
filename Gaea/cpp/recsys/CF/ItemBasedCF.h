#ifndef ITEMBASEDCF_H
#define ITEMBASEDCF_H

#include "../util/RatingMatrixStatic.h"

namespace ycg {

struct ItemModelNode {
	int itemID;
	double sim;
};

class ItemModelNodeComparator {
public:
	int operator() (const ItemModelNode& lhs, const ItemModelNode& rhs) {
		return (lhs.sim < rhs.sim)?1:-1;
	}
};

class ItemBasedCF {
public:
	ItemBasedCF(RatingMatrixStatic& rms, int similarityType = SIM_ADJUSTED_COSINE,
			int modelType = MODEL_NEAREST_K, int nearsestK = 50,
			int predictionType = PRED_WEIGHTED_SUM);
	virtual ~ItemBasedCF();
	virtual void train();
	virtual double predictRating(int userID, int itemID);
protected:
	double computeSim(int itemID1, int itemID2);
	void computeNearestK(int itemID);
	double predictRatingWeightedSum(int userID, int itemID);
	double predictRatingRegression(int userID, int itemID);
public:
	static const int SIM_COSINE = 1;
	static const int SIM_CORRELATION = 2;
	static const int SIM_ADJUSTED_COSINE = 3;
	static const int MODEL_NEAREST_K = 4;
	static const int MODEL_ALL = 5;
	static const int PRED_WEIGHTED_SUM = 6;
	static const int PRED_REGRESSION = 7;
	static const int PRED_USER_AVERAGE = 8;
	static const int PRED_ITEM_AVERAGE = 9;
protected:
	RatingMatrixStatic& rMat;
	int numUser;
	int numItem;
	int simType;
	int modelType;
	int nearsestK;
	int predType;
	double **simMat;
	ItemModelNode **simList;
	static const double eps;
};

} //~ namespace ycg

#endif /* ITEMBASEDCF_H_ */
