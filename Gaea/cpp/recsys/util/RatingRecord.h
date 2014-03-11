#ifndef RATINGRECORD_H
#define RATINGRECORD_H

namespace ycg {

class RatingRecord {
public:
	RatingRecord() :
		_userID(0),
		_itemID(0),
		_rating(0.0) { }
	RatingRecord(int userID, int itemID, double rating) :
		_userID(userID),
		_itemID(itemID),
		_rating(rating) { }
	int userID() const {
		return _userID;
	}
	int itemID() const {
		return _itemID;
	}
	double rating() const {
		return _rating;
	}
	void setRating(double rating) {
		_rating = rating;
	}
private:
	int _userID;
	int _itemID;
	double _rating;
};

} //~ namespace ycg

#endif /* RATINGRECORD_H */
