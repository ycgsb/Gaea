#include "Statistic.h"
#include <cmath>
#include <cassert>
#include <cstdio>

namespace ycg {

const double Statistic::EPS = 1e-200;

double Statistic::pearsonCorrelation(const double *vec1, const double *vec2, int size) {
	double avg1 = 0.0;
	double avg2 = 0.0;
	for (int i = 0; i < size; ++i) {
		avg1 += vec1[i];
		avg2 += vec2[i];
	}
	avg1 /= size;
	avg2 /= size;
	double prod = 0.0;
	double norm1 = 0.0;
	double norm2 = 0.0;
	for (int i = 0; i < size; ++i) {
		double v1 = vec1[i] - avg1;
		double v2 = vec2[i] - avg2;
		prod += v1 * v2;
		norm1 += v1 * v1;
		norm2 += v2 * v2;
	}
	double corr = prod / (sqrt(norm1*norm2) + EPS);
	return corr;
}

double Statistic::cosineCorrelation(const double *vec1, const double *vec2, int size) {
	double prod = 0.0;
	double norm1 = 0.0, norm2 = 0.0;
	for (int i = 0; i < size; ++i) {
		prod += vec1[i] * vec2[i];
		norm1 += vec1[i] * vec1[i];
		norm2 += vec2[i] * vec2[i];
	}
	double corr = prod / (sqrt(norm1*norm2) + EPS);
	return corr;
}

double Statistic::meanSquareError(const double *vec1, const double *vec2, int size) {
	double dist = 0.0;
	for (int i = 0; i < size; ++i) {
		double d = vec1[i]-vec2[i];
		dist += d*d;
	}
	dist = sqrt(dist/size);
	return dist;
}

} //~ namespace ycg
