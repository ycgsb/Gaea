#ifndef RATINGUTIL_H
#define RATINGUTIL_H

#include "RatingMatSparse.h"

namespace ycg {

class RatingUtil {
public:
	static void computeUserAverage(const RatingMatSparse& ratingMS, double *userAverage);
	static void computeItemAverage(const RatingMatSparse& ratingMS, double *itemAverage);
};

} //~ namespace ycg

#endif /* RATINGUTIL_H_ */
