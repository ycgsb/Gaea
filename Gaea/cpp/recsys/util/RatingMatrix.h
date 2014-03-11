#ifndef RATINGMATRIX_H
#define RATINGMATRIX_H

#include "RatingRecord.h"
#include "../../numerical/Matrix.h"
#include <cassert>

namespace ycg {

class RatingMatrix {
public:
	RatingMatrix(int numUser, int numItem, int numRating, const RatingRecord* ratingArray);
	virtual ~RatingMatrix();
	int numUser() const  {
		return _numUser;
	}
	int numItem() const {
		return _numItem;
	}
	int numRating() const {
		return _numRating;
	}
	double rating(int userID, int itemID) const {
		assert(userID >= 0 && userID < numUser());
		assert(itemID >= 0 && itemID < numItem());
		return mat[userID][itemID];
	}
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
		return _userCount[userID];
	}
	int itemCount(int itemID) const {
		assert(itemID >= 0 && itemID < numItem());
		return _itemCount[itemID];
	}
	double sparsity() const {
		return 1.0 - static_cast<double>(_numRating) / (static_cast<double>(_numUser*_numItem));
	}
	class IteratorCol;
	class IteratorRow;
	friend class IteratorCol;
	friend class IteratorRow;
	class IteratorCol {
	public:
		IteratorCol(const RatingMatrix *rm, int row, int col) {
			this->rm = rm;
			i = row;
			j = col;
		}
		bool operator != (const IteratorCol& rhs) {
			return this->i != rhs.i;
		}
		IteratorCol& operator ++() {
			++i;
			while (i < rm->_numUser && rm->mat[i][j] == 0.0) {
				++i;
			}
			return *this;
		}
		RatingRecord operator *() {
			return RatingRecord(i, j, rm->mat[i][j]);
		}
	private:
		const RatingMatrix *rm;
		int i;
		int j;
	};
	class IteratorRow {
	public:
		IteratorRow(const RatingMatrix *rm, int row, int col) {
			this->rm = rm;
			i = row;
			j = col;
		}
		bool operator != (const IteratorRow& rhs) {
			return this->j != rhs.j;
		}
		IteratorRow& operator ++() {
			++j;
			while (j < rm->_numItem && rm->mat[i][j] == 0.0) {
				++j;
			}
			return *this;
		}
		RatingRecord operator *() {
			return RatingRecord(i, j, rm->mat[i][j]);
		}
	private:
		const RatingMatrix *rm;
		int i;
		int j;
	};
	IteratorCol beginCol(int col) const {
		return IteratorCol(this, 0, col);
	}
	IteratorCol endCol(int col) const {
		return IteratorCol(this, _numUser, col);
	}
	IteratorRow beginRow(int row) const {
		return IteratorRow(this, row, 0);
	}
	IteratorRow endRow(int row) const {
		return IteratorRow(this, row, _numItem);
	}
private:
	int _numUser;
	int _numItem;
	int _numRating;
	Matrix mat;
	double *_itemAverage;
	double *_userAverage;
	int *_itemCount;
	int *_userCount;
};

} //~ namespace ycg

#endif /* RATINGMATRIX_H_ */
