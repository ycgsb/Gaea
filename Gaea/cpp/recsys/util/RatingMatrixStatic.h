#ifndef RATINGMATRIXSTATIC_H
#define RATINGMATRIXSTATIC_H

#include "RatingRecord.h"
#include <cassert>

namespace ycg {

class RatingMatrixStatic {
public:
	RatingMatrixStatic(int numUser, int numItem, int numRating, const RatingRecord *ratingArray);
	virtual ~RatingMatrixStatic();
    int numUser() const  { return _numUser; }
    int numItem() const { return _numItem; }
    int numRating() const { return _numRating; }
	double itemAverage(int itemID) const {
		assert(itemID >= 0 && itemID < numItem());
		return _itemAverage[itemID];
	}
	double userAverage(int userID) const {
		assert(userID >= 0 && userID < numUser());
		return 	_userAverage[userID];
	}
	int userCount(int userID) const {
		assert(userID >= 0 && userID < numUser());
		return _rowCount[userID];
	}
	int itemCount(int itemID) const {
		assert(itemID >= 0 && itemID < numItem());
		return _colCount[itemID];
	}
	double sparsity() const {
		return 1.0 - static_cast<double>(_numRating) / (static_cast<double>(_numUser*_numItem));
	}
	double rating(int userID, int itemID) const;
	void adjustByMinusUserAverage();
	void adjustByMinusItemAverage();
	class IteratorRow;
	class IteratorCol;
	friend class IteratorRow;
	friend class IteratorCol;
	class IteratorCol {
	public:
		IteratorCol(const RatingMatrixStatic *rms, int pos) {
			this->rms = rms;
			this->pos = pos;
		}
		bool operator != (const IteratorCol& rhs) {
			return this->pos != rhs.pos;
		}
		IteratorCol& operator ++() {
			++pos;
			return *this;
		}
		RatingRecord& operator *() {
			return rms->_colMajor[pos];
		}
	private:
		const RatingMatrixStatic *rms;
		int pos;
	};
	class IteratorRow {
	public:
		IteratorRow(const RatingMatrixStatic *rms, int pos) {
			this->rms = rms;
			this->pos = pos;
		}
		bool operator != (const IteratorRow& rhs) {
			return this->pos != rhs.pos;
		}
		IteratorRow& operator ++() {
			++pos;
			return *this;
		}
		RatingRecord& operator *() {
			return rms->_rowMajor[pos];
		}
	private:
		const RatingMatrixStatic *rms;
		int pos;
	};
	IteratorCol beginCol(int col) const {
		return IteratorCol(this, _colBegin[col]);
	}
	IteratorCol endCol(int col) const {
		return IteratorCol(this, _colBegin[col]+_colCount[col]);
	}
	IteratorRow beginRow(int row) const {
		return IteratorRow(this, _rowBegin[row]);
	}
	IteratorRow endRow(int row) const {
		return IteratorRow(this, _rowBegin[row]+_rowCount[row]);
	}
private:
	int _numUser;
	int _numItem;
	int _numRating;
    int *_colCount;
    int *_rowCount;
	RatingRecord *_rowMajor;
	RatingRecord *_colMajor;
	int *_rowBegin;
	int *_colBegin;
	double *_itemAverage;
	double *_userAverage;


};

} //~ namespace ycg

#endif /* RATINGMATRIXSTATIC_H */
