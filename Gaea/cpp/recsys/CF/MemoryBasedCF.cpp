#include "MemoryBasedCF.h"

namespace ycg {

MemoryBasedCF::MemoryBasedCF(const RatingList& rlist) :
	_ratingMS(rlist) { }

MemoryBasedCF::~MemoryBasedCF() { }

} //~ namespace ycg
