#ifndef STATISTIC_H
#define STATISTIC_H

namespace ycg {

class Statistic {
public:
	static const double EPS;
	static double pearsonCorrelation(const double *vec1, const double *vec2, int size);
	static double cosineCorrelation(const double *vec1, const double *vec2, int size);
	static double meanSquareError(const double *vec1, const double *vec2, int size);




};

} //~ namespace ycg

#endif /* STATISTIC_H */
