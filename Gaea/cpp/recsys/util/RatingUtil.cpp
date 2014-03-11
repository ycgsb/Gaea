#include "RatingUtil.h"
#include <cassert>

namespace ycg {

void RatingUtil::computeUserAverage(const RatingMatSparse& ratingMS, double *userAverage) {
	for (int i = 0; i < ratingMS._rows; ++i) {
		double sum = 0.0;
		for (int j = ratingMS._rowBegin[i],	end = j + ratingMS._rowCount[i]; j < end; ++j) {
			int pos = ratingMS._rowList[j].valPos;
			sum += ratingMS._values[pos];
		}
		userAverage[i] = (ratingMS._rowCount[i] > 0) ?
					sum / ratingMS._rowCount[i] : 0.0;
	}
}

void RatingUtil::computeItemAverage(const RatingMatSparse& ratingMS, double *itemAverage) {
	for (int j = 0; j < ratingMS._cols; ++j) {
		double sum = 0.0;
		for (int i = ratingMS._colBegin[j], end = i + ratingMS._colCount[j]; i < end; ++i) {
			int pos = ratingMS._colList[i].valPos;
			sum += ratingMS._values[pos];
		}
		itemAverage[j] = (ratingMS._colCount[j] > 0) ?
				sum / ratingMS._colCount[j] : 0.0;
	}
}

} //~ namespace ycg
