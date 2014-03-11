#include "ItemBasedCF.h"
#include "../../algorithms/sort/RandomizedSelector.h"
#include "../../math/Math.h"
#include <cstdio>
#include <cstdlib>

namespace ycg {

ItemBasedCF::ItemBasedCF(RatingMatrixStatic& rms, int similarityType, int modelType,
		int nearestK, int predictionType) :
	rMat(rms) {
	numUser = rms.numUser();
	numItem = rms.numItem();
	this->simType = similarityType;
	if (similarityType == SIM_CORRELATION) {
		rMat.adjustByMinusItemAverage();
	} else if (similarityType == SIM_ADJUSTED_COSINE) {
		rMat.adjustByMinusUserAverage();
	}
	this->modelType = modelType;
	simMat = new double*[numItem];
	for (int i = 0; i < numItem; ++i) {
		simMat[i] = new double[numItem];
	}
	if (modelType == MODEL_NEAREST_K) {
		this->nearsestK = nearestK;
		simList = new ItemModelNode*[numItem];
		for (int i = 0; i < numItem; ++i) {
			simList[i] = new ItemModelNode[nearestK];
		}
	}
	this->predType = predictionType;
}

ItemBasedCF::~ItemBasedCF() {
	for (int i = 0; i < numItem; ++i) {
		delete []simMat[i];
	}
	delete []simMat;
	if (modelType == MODEL_NEAREST_K) {
		for (int i = 0; i < numItem; ++i) {
			delete simList[i];
		}
		delete []simList;
	}
}

void ItemBasedCF::train() {
	for (int i = 0; i < numItem; ++i) {
		simMat[i][i] = 1.0;
		for (int j = i + 1; j < numItem; ++j) {
			simMat[i][j] = simMat[j][i] = computeSim(i, j);
		}
	}
	if (modelType == MODEL_NEAREST_K) {
		for (int i = 0; i < numItem; ++i) {
			computeNearestK(i);
		}
	}
}

double ItemBasedCF::predictRating(int userID, int itemID) {
	assert(userID >= 0 && userID < numUser);
	assert(itemID >= 0 && itemID < numItem);
	switch (predType) {
		case PRED_WEIGHTED_SUM:
			return predictRatingWeightedSum(userID, itemID);
		case PRED_REGRESSION:
			return predictRatingRegression(userID, itemID);
		case PRED_USER_AVERAGE:
			return rMat.userAverage(userID);
		case PRED_ITEM_AVERAGE:
			return rMat.itemAverage(itemID);
		default:
			return 0.0;
	}
}

const double ItemBasedCF::eps = 1e-200;

double ItemBasedCF::computeSim(int itemID1, int itemID2) {
	double sum = 0.0;
	double norm1 = 0.0, norm2 = 0.0;
	auto iter1 = rMat.beginCol(itemID1);
	auto iter1End = rMat.endCol(itemID1);
	auto iter2 = rMat.beginCol(itemID2);
	auto iter2End = rMat.endCol(itemID2);
	while (iter1 != iter1End && iter2 != iter2End) {
		RatingRecord& rr1 = *iter1;
		RatingRecord& rr2 = *iter2;
		if (rr1.userID() == rr2.userID()) {
			sum += rr1.rating()*rr2.rating();
			norm1 += rr1.rating()*rr1.rating();
			norm2 += rr2.rating()*rr2.rating();
			++iter1;
			++iter2;
		} else if (rr1.userID() < rr2.userID()) {
			++iter1;
		} else if (rr1.userID() > rr2.userID()) {
			++iter2;
		}
	}
	double sim = sum / (sqrt(norm1*norm2)+eps);
	return sim;
}

void ItemBasedCF::computeNearestK(int itemID) {
	ItemModelNode *temp = new ItemModelNode[numItem];
	for (int j = 0; j < numItem; ++j) {
		temp[j].itemID = j;
		temp[j].sim = simMat[itemID][j];
	}
	RandomizedSelector<ItemModelNode> select;
	select(temp, numItem, nearsestK - 1, ItemModelNodeComparator());
	for (int j = 0; j < nearsestK; ++j) {
		simList[itemID][j] = temp[j];
	}
	delete []temp;
}

double ItemBasedCF::predictRatingWeightedSum(int userID, int itemID) {
	if (modelType == MODEL_ALL) {
		auto iter = rMat.beginRow(userID);
		auto iterEnd = rMat.endRow(userID);
		double sum1 = 0.0, sum2 = 0.0;
		while (iter != iterEnd) {
			RatingRecord& rr = *iter;
			double sim = simMat[itemID][rr.itemID()];
			double r = rr.rating();
			if (sim > 0.0) {
				sum1 += sim * r;
				sum2 += sim;
			}
			++iter;
		}
		double predRating = sum1 / (sum2 + eps);
		if (simType == SIM_COSINE) {
			return predRating;
		} else if (simType == SIM_CORRELATION) {
			return predRating + rMat.itemAverage(itemID);
		} else if (simType == SIM_ADJUSTED_COSINE) {
			return predRating + rMat.userAverage(userID);
		}
	} else if (modelType == MODEL_NEAREST_K) {
		double sum1 = 0.0, sum2 = 0.0;
		int count = 0;
		for (int i = 0; i < nearsestK; ++i) {
			int j = simList[itemID][i].itemID;
			double sim = simList[itemID][i].sim;
			double r = rMat.rating(userID, j);
			if (r > -1000.0 && sim > 0.0) {
				sum1 += sim * r;
				sum2 += sim;
				++count;
			}
		}
		if (count > 0) {
			double predRating = sum1 / (sum2 + eps);
			if (simType == SIM_COSINE) {
				return predRating;
			} else if (simType == SIM_CORRELATION) {
				return predRating + rMat.itemAverage(itemID);
			} else if (simType == SIM_ADJUSTED_COSINE) {
				return predRating + rMat.userAverage(userID);
			}
		} else {
			return 0.0;
		}
	} else {
		return 0.0;
	}
}

double ItemBasedCF::predictRatingRegression(int userID, int itemID) {
	return 0.0;
}

} //~ namespace ycg
