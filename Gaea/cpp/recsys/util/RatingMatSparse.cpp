#include "RatingMatSparse.h"
#include "../../algorithms/sort/CountingSorter.h"
#include "../../algorithms/search/BinarySearch.h"
#include <cstdio>

namespace ycg {

RatingMatSparse::RatingMatSparse(const RatingList &rlist) :
	_rows(rlist.numUser()),
	_cols(rlist.numItem()),
	_numElem(rlist.numRating()),
	_lowestRating(rlist.lowestRating()),
	_highestRating(rlist.highestRating()) {
	_rowCount = new int[_rows];
	_rowBegin = new int[_rows];
	for (int i = 0; i < _rows; ++i) {
		_rowCount[i] = 0;
		_rowBegin[i] = -1;
	}
	_colCount = new int[_cols];
	_colBegin = new int[_cols];
	for (int j = 0; j < _cols; ++j) {
		_colCount[j] = 0;
		_colBegin[j] = -1;
	}
	ElemNode *elems= new ElemNode[_numElem];
	_values = new double[_numElem];
	for (int i = 0; i < _numElem; ++i) {
		const RatingRecord& rr = rlist.get(i);
		_values[i] = rr.rating();
		elems[i].row = rr.userID();
		elems[i].col = rr.itemID();
		elems[i].valPos = i;
		++_rowCount[rr.userID()];
		++_colCount[rr.itemID()];
	}
	auto row2int = [&](const ElemNode& en){ return en.row;};
	auto col2int = [&](const ElemNode& en){ return en.col;};
	CountingSorter<ElemNode> sort;
	sort(elems, _numElem, col2int, _cols);
	sort(elems, _numElem, row2int, _rows);
	_rowList = new RowNode[_numElem];
	for (int i = _numElem - 1; i >= 0; --i) {
		_rowBegin[elems[i].row] = i;
		_rowList[i].col = elems[i].col;
		_rowList[i].valPos = elems[i].valPos;
	}
	sort(elems, _numElem, row2int, _rows);
	sort(elems, _numElem, col2int, _cols);
	_colList = new ColNode[_numElem];
	for (int i = _numElem - 1; i >= 0; --i) {
		_colBegin[elems[i].col] = i;
		_colList[i].row = elems[i].row;
		_colList[i].valPos = elems[i].valPos;
	}
	delete []elems;
}

RatingMatSparse::~RatingMatSparse() {
	delete []_colList;
	delete []_rowList;
	delete []_values;
	delete []_colBegin;
	delete []_colCount;
	delete []_rowBegin;
	delete []_rowCount;
}

bool RatingMatSparse::exist(int row, int col) const {
	assert(row >= 0 && row < _rows);
	assert(col >= 0 && col < _cols);
	int rbegin = _rowBegin[row];
	int rsize = _rowCount[row];
	BinarySearch bsearch;
    int pos = bsearch(col, &_rowList[rbegin], rsize, [&](const int& lhs, const RowNode& rhs){ return lhs - rhs.col; });
    return (pos >= 0);
}

double& RatingMatSparse::operator() (int row, int col) {
	return const_cast<double&>(const_cast<const RatingMatSparse*>(this)->operator ()(row, col));
}

const double& RatingMatSparse::operator() (int row, int col) const {
	assert(row >= 0 && row < _rows);
	assert(col >= 0 && col < _cols);
	int rbegin = _rowBegin[row];
	int rsize = _rowCount[row];
	BinarySearch bsearch;
	int pos = bsearch(col, &_rowList[rbegin], rsize, [&](const int& lhs, const RowNode& rhs){ return lhs - rhs.col; });
	assert(pos >= 0);
	return _values[_rowList[rbegin+pos].valPos];
}

} //~ namespace ycg
