#ifndef RATINGLIST_H
#define RATINGLIST_H

#include "RatingRecord.h"
#include "../../util/ArrayList.h"

namespace ycg {

class RatingList {
public:
	RatingList(int numUser, int numItem, int numRating, double lowestRating, double highestRating);
	RatingList(RatingList&& orig);
	virtual ~RatingList();
	int numUser() const { return _numUser; }
	int numItem() const { return _numItem; }
	int numRating() const { return _numRating; }
	double lowestRating() const { return _lowestRating; }
	double highestRating() const { return _highestRating; }
	RatingList& add(const RatingRecord& record) {
		_ratingArray->add(record);
		return *this;
	}
	const RatingRecord& get(int index) const {
		return _ratingArray->get(index);
	}
private:
	RatingList(const RatingList& orig);
private:
	ArrayList<RatingRecord> *_ratingArray;
	int _numUser;
	int _numItem;
	int _numRating;
	double _lowestRating;
	double _highestRating;
};

} //~ namespace ycg

#endif /* RATINGLIST_H */
