#include "POP.h"
#include "../util/RatingUtil.h"
#include "../../util/Random.h"
#include "../../time/Stopwatch.h"
#include "../../algorithms/sort/QuickSorter.h"
#include <cstdio>
#include <cstdlib>

namespace ycg {

POP::POP(const RatingList& rlist, const POPConfig& config) :
	MemoryBasedCF(rlist),
	_config(config),
	_itemAverage(_ratingMS.numItem(), 0.0),
	_userAverage(_ratingMS.numUser(), 0.0),
	_sortedItems(_ratingMS.numItem()),
	_trainDone(false) { }

POP::~POP() { }

void POP::train() {
	printf("POP::train...");
	RatingUtil::computeItemAverage(_ratingMS, _itemAverage);
	sortItemByAverage();
	RatingUtil::computeUserAverage(_ratingMS, _userAverage);
	printf("done.\n");
}

void POP::sortItemByAverage() {
	int size = _ratingMS.numItem();
	for (int i = 0; i < size; ++i) {
		_sortedItems[i].rating = _itemAverage[i];
		_sortedItems[i].itemID = i;
	}
	QuickSorter sort;
	sort(_sortedItems.begin(), _sortedItems.size(), [&](const RatingAndItemID& lhs, const RatingAndItemID& rhs)->int
			{ return (lhs.rating < rhs.rating)? 1 : -1;});
}

double POP::predictRating(int userID, int itemID) {
	if (_config.PRED_METHOD ==  POPConfig::PRED_ITEM_AVERAGE) {
		return _itemAverage[itemID];
	} else if (_config.PRED_METHOD == POPConfig::PRED_USER_AVERAGE) {
		return _userAverage[userID];
	} else if (_config.PRED_METHOD == POPConfig::PRED_RANDOM) {
		return Random::instance().uniform(_ratingMS.lowestRating(),_ratingMS.highestRating());
	} else {
		return 0.0;
	}
}

ArrayList<int> POP::recommendTopN(int userID, int n) {
	if (_config.RANK_METHOD == POPConfig::RANK_RANDOM) {
		return computeTopNByRandom(userID, n);
	} else if (_config.RANK_METHOD == POPConfig::RANK_ITEM_AVERAGE) {
		return computeTopNByItemAverage(userID, n);
	} else {
		return ArrayList<int>();
	}
}

ArrayList<int> POP::computeTopNByRandom(int userID, int n) {
	int *notRatedItems = new int[_ratingMS.numItem()];
	int cnt = 0;
	for (int i = 0; i < _ratingMS.numItem(); ++i) {
		if (!_ratingMS.exist(userID, i)) {
			notRatedItems[cnt++] = i;
		}
	}
	Random::instance().shuffle(notRatedItems, cnt);
	ArrayList<int> recItems(0, n);
	for (int i = 0; i < n; ++i) {
		recItems.add(notRatedItems[i]);
	}
	delete [] notRatedItems;
	return recItems;
}

ArrayList<int> POP::computeTopNByItemAverage(int userID, int n) {
	ArrayList<int> recItems(0, n);
	for (int i = 0; i < _sortedItems.size(); ++i) {
		int itemID = _sortedItems[i].itemID;
		if (!_ratingMS.exist(userID, itemID)) {
			recItems.add(itemID);
			if (recItems.size() >= n) break;
		}
	}
	return recItems;
}

} //~ namespace ycg
