#include "RatingMatrixStatic.h"
#include "../../algorithms/sort/CountingSorter.h"
#include "../../algorithms/search/BinarySearch.h"
#include <cstdio>

namespace ycg {

RatingMatrixStatic::RatingMatrixStatic(int numUser, int numItem, int numRating, const RatingRecord *ratingArray) :
		_numUser(numUser),
		_numItem(numItem),
		_numRating(numRating) {
    _userAverage = new double[numUser];
	_rowCount = new int[numUser];
	_rowBegin = new int[numUser];
	for (int i = 0; i < numUser; ++i) {
		_userAverage[i] = 0.0;
		_rowCount[i] = 0;
		_rowBegin[i] = -1;
    }
	_itemAverage = new double[numItem];
	_colCount = new int[numItem];
	_colBegin = new int[numItem];
	for (int j = 0; j < numItem; ++j) {
		_colCount[j] = 0;
		_itemAverage[j] = 0.0;
		_colBegin[j] = -1;
	}
	_rowMajor = new RatingRecord[numRating];
	_colMajor = new RatingRecord[numRating];
	for (int i = 0; i < numRating; ++i) {
		const RatingRecord& rr = ratingArray[i];
		_rowMajor[i] = rr;
		_colMajor[i] = rr;
        _userAverage[rr.userID()] += rr.rating();
        ++_rowCount[rr.userID()];
        _itemAverage[rr.itemID()] += rr.rating();
        ++_colCount[rr.itemID()];
	}
	for (int i = 0; i < numUser; ++i) {
		if (_rowCount[i] > 0) {
			_userAverage[i] /= _rowCount[i];
		}
	}
	for (int i = 0; i < numItem; ++i) {
		if (_colCount[i] > 0) {
			_itemAverage[i] /= _colCount[i];
		}
	}
//	class RatingRecordToIntByRow {
//	public:
//		int operator() (const RatingRecord& r) { return r.userID();	}
//	} cvt1;
//	class RatingRecordToIntByCol {
//	public:
//		int operator() (const RatingRecord& r) { return r.itemID();	}
//	} cvt2;
	auto cvt1 =[&](const RatingRecord& r){ return r.userID();};
	auto cvt2 =[&](const RatingRecord& r){ return r.itemID();};
	CountingSorter<RatingRecord> sort;
	sort(_rowMajor, numRating, cvt2, numItem);
	sort(_rowMajor, numRating, cvt1, numUser);
	sort(_colMajor, numRating, cvt1, numUser);
	sort(_colMajor, numRating, cvt2, numItem);
	for (int i = 0; i < numRating; ++i) {
		_rowBegin[_rowMajor[i].userID()] = i;
		while (i+1 < numRating && _rowMajor[i].userID() == _rowMajor[i+1].userID()) {
			++i;
        }
	}
	for (int i = 0; i < numRating; ++i) {
		_colBegin[_colMajor[i].itemID()] = i;
		while (i+1 < numRating && _colMajor[i].itemID() == _colMajor[i+1].itemID()) {
			++i;
		}
	}
}

RatingMatrixStatic::~RatingMatrixStatic() {
	delete []_colMajor;
	delete []_rowMajor;
	delete []_colBegin;
	delete []_rowBegin;
	delete []_userAverage;
	delete []_rowCount;
	delete []_itemAverage;
	delete []_colCount;
}

double RatingMatrixStatic::rating(int userID, int itemID) const {
    assert(userID >= 0 && userID < numUser());
	assert(itemID >= 0 && itemID < numItem());
    int rbegin = _rowBegin[userID];
    int rsize = _rowCount[userID];
    class RatingRecordComparatorByCol {
    public:
    	int operator() (const RatingRecord& lhs, const RatingRecord& rhs) {
    		return lhs.itemID() - rhs.itemID();
    	}
    } cmp;
    RatingRecord key(userID, itemID, 0.0);
    BinarySearch bsearch;
    int pos = bsearch(key, _rowMajor + rbegin, rsize, cmp);
    if (pos >= 0) {
    	return _rowMajor[rbegin+pos].rating();
    } else {
    	return -1000.0;
    }
}

void RatingMatrixStatic::adjustByMinusUserAverage() {
	for (int i = 0; i < _numRating; ++i) {
		RatingRecord& rr1 = _rowMajor[i];
		rr1.setRating(rr1.rating() - _userAverage[rr1.userID()]);
		RatingRecord& rr2 = _colMajor[i];
		rr2.setRating(rr2.rating() - _userAverage[rr2.userID()]);
	}
}

void RatingMatrixStatic::adjustByMinusItemAverage() {
	for (int i = 0; i < _numRating; ++i) {
		RatingRecord& rr1 = _rowMajor[i];
		rr1.setRating(rr1.rating() - _itemAverage[rr1.itemID()]);
		RatingRecord& rr2 = _colMajor[i];
		rr2.setRating(rr2.rating() - _itemAverage[rr2.itemID()]);
	}
}

} //~ namespace ycg
