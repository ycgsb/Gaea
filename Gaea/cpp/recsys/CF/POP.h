#ifndef POP_H
#define POP_H

#include "MemoryBasedCF.h"
#include "../../lang/Array1D.h"
#include "../../util/Pair.h"
#include "../../util/ArrayList.h"

namespace ycg {

struct POPConfig {
	enum Method {
		PRED_USER_AVERAGE,
		PRED_ITEM_AVERAGE,
		PRED_RANDOM,
		RANK_ITEM_AVERAGE,
		RANK_RANDOM
	};
	Method PRED_METHOD;
	Method RANK_METHOD;
};

class POP : public MemoryBasedCF {
public:
	POP(const RatingList& rlist, const POPConfig& config);
	virtual ~POP();
	void train();
	double predictRating(int userID, int itemID);
	ArrayList<int> recommendTopN(int userID, int n);
private:
	void sortItemByAverage();
	ArrayList<int> computeTopNByRandom(int userID, int n);
	ArrayList<int> computeTopNByItemAverage(int userID, int n);
private:
	const POPConfig& _config;
	struct RatingAndItemID {
		double rating;
		int itemID;
	};
	Array1D<double> _itemAverage;
	Array1D<RatingAndItemID> _sortedItems;
	Array1D<double> _userAverage;
	bool _trainDone;
};

} //~ namespace ycg

#endif /* POP_H */
