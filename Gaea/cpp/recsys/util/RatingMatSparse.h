#ifndef RATINGMATSPARSE_H
#define RATINGMATSPARSE_H

#include "RatingList.h"

namespace ycg {

class RatingMatSparse {
public:
	RatingMatSparse(const RatingList& rlist);
	virtual ~RatingMatSparse();
	int numUser() const  { return _rows; }
	int numItem() const { return _cols; }
	int numRating() const { return _numElem; }
	int rows() const { return _rows; }
	int cols() const { return _cols; }
	double sparsity() const { return 1.0 - (_numElem) / (static_cast<double>(_rows)*_cols);	}
	double lowestRating() const { return _lowestRating; }
	double highestRating() const { return _highestRating; }
	int rowCount(int i) const { return _rowCount[i]; }
	int colCount(int j) const { return _colCount[j]; }
	class IteratorRow;
	friend class IteratorRow;
	class IteratorCol;
	friend class IteratorCol;
	friend class RatingUtil;
	class IteratorRow {
	public:
		IteratorRow(const RatingMatSparse *rms, int row, int pos) :
			_rms(rms), _row(row), _pos(pos) { }
		bool operator != (const IteratorRow& rhs) { return _pos != rhs._pos; }
		IteratorRow& operator ++() {
			++_pos;
			return *this;
		}
		RatingRecord operator *() {
			return RatingRecord(_row, _rms->_rowList[_pos].col,
					_rms->_values[_rms->_rowList[_pos].valPos]);
		}
	private:
		const RatingMatSparse *_rms;
		int _row;
		int _pos;
	};
	class IteratorCol {
	public:
		IteratorCol(const RatingMatSparse *rms, int col, int pos) :
			_rms(rms), _col(col), _pos(pos) { }
		bool operator != (const IteratorCol& rhs) {	return _pos != rhs._pos; }
		IteratorCol& operator ++() {
			++_pos;
			return *this;
		}
		RatingRecord operator *() {
			return RatingRecord(_rms->_colList[_pos].row, _col,
					_rms->_values[_rms->_colList[_pos].valPos]);
		}
	private:
		const RatingMatSparse *_rms;
		int _col;
		int _pos;
	};
	IteratorRow beginRow(int row) const {
		return IteratorRow(this, row, _rowBegin[row]);
	}
	IteratorRow endRow(int row) const {
		return IteratorRow(this, row, _rowBegin[row]+_rowCount[row]);
	}
	IteratorCol beginCol(int col) const {
		return IteratorCol(this, col, _colBegin[col]);
	}
	IteratorCol endCol(int col) const {
		return IteratorCol(this, col, _colBegin[col]+_colCount[col]);
	}
	bool exist(int row, int col) const;
	double& operator() (int row, int col);
	const double& operator() (int row, int col) const;
private:
	struct ElemNode {
		int row, col;
		int valPos;
	};
	struct RowNode {
		int col;
		int valPos;
	};
	struct ColNode {
		int row;
		int valPos;
	};
	int _rows;
	int _cols;
	int _numElem;
	int *_rowCount;
    int *_rowBegin;
    int *_colCount;
   	int *_colBegin;
	RowNode *_rowList;
	ColNode *_colList;
	double *_values;
	double _lowestRating;
	double _highestRating;
};

} //~ namespace ycg

#endif /* RATINGMATSPARSE_H_ */
