#include "RatingList.h"
#include <cstdio>

namespace ycg {

RatingList::RatingList(int numUser, int numItem, int numRating, double lowestRating, double highestRating) :
	_numUser(numUser),
	_numItem(numItem),
	_numRating(numRating),
	_lowestRating(lowestRating),
	_highestRating(highestRating) {
	_ratingArray = new ArrayList<RatingRecord>(0, numRating);
}

RatingList::~RatingList() {
	delete _ratingArray;
}

RatingList::RatingList(RatingList&& orig) {
	_numUser = orig._numUser;
	_numItem = orig._numItem;
	_numRating = orig._numRating;
	_lowestRating = orig._lowestRating;
	_highestRating = orig._highestRating;
	_ratingArray = orig._ratingArray;
	orig._ratingArray = nullptr;
}

} //~ namespace ycg
