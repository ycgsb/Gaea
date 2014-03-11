#ifndef MEMORYBASEDCF_H
#define MEMORYBASEDCF_H

#include "../util/RatingList.h"
#include "../util/RatingMatSparse.h"

namespace ycg {

class MemoryBasedCF {
protected:
	MemoryBasedCF(const RatingList& rlist);
	virtual ~MemoryBasedCF();
protected:
	RatingMatSparse _ratingMS;
};

} //~ namespace ycg

#endif /* MEMORYBASEDCF_H_ */
