#include "RatingMatrix.h"
#include <cstdio>

namespace ycg {

RatingMatrix::RatingMatrix(int numUser, int numItem, int numRating, const RatingRecord *ratingArray) :
	_numUser(numUser),
	_numItem(numItem),
	_numRating(numRating),
	mat(numUser, numItem, 0.0),
	_userAverage(new double[numUser]),
	_userCount(new int[numUser]),
	_itemAverage(new double[numItem]),
	_itemCount(new int[numItem]) {
	for (int i = 0; i < numUser; ++i) {
		_userCount[i] = 0;
		_userAverage[i] = 0.0;
	}
	for (int j = 0; j < numItem; ++j) {
		_itemCount[j] = 0;
		_itemAverage[j] = 0.0;
	}
	for (int i = 0; i < numRating; ++i) {
		int row = ratingArray[i].userID();
		int col = ratingArray[i].itemID();
		double val = ratingArray[i].rating();
		mat[row][col] = val;
		_userAverage[row] += val;
		_itemAverage[col] += val;
		++_userCount[row];
		++_itemCount[col];
	}
	for (int i = 0; i < numUser; ++i) {
		if (_userCount[i] > 0) {
			_userAverage[i] /= _userCount[i];
		}
	}
	for (int j = 0; j < numItem; ++j) {
		if (_itemCount[j] > 0) {
			_itemAverage[j] /= _itemCount[j];
		}
	}
}

RatingMatrix::~RatingMatrix() {
	delete []_userAverage;
	delete []_userCount;
	delete []_itemAverage;
	delete []_itemCount;
}

} //~ namespace ycg
