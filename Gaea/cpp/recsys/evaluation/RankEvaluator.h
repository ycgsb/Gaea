#ifndef RANKEVALUATOR_H
#define RANKEVALUATOR_H

#include "../util/RatingList.h"
#include "../../algorithms/sort/QuickSorter.h"
#include "../../util/ArrayList.h"
#include <cstdio>

namespace ycg {

struct RankEvaluatorConfig {
	enum Method {
		METHOD_PRECISION,
		METHOD_RECALL,
		METHOD_F1
	};
	Method METHOD;
	ArrayList<int> RANK_SIZE;
};

template <class Model>
class RankEvaluator {
public:
	RankEvaluator(Model& model, const RatingList& rlist, const RankEvaluatorConfig& config);
	virtual ~RankEvaluator() { }
	void evaluate();
private:
	void computeGroundTruth();
	void computePrecision(int n);
	void computeRecall(int n);
	void computeF1(int n);
private:
	Model& _model;
	const RatingList& _rlist;
	const RankEvaluatorConfig& _config;
	struct RatingAndItemID {
		double rating;
		int itemID;
	};
	Array1D<ArrayList<RatingAndItemID>> _gtRank;
};

template <class Model>
RankEvaluator<Model>::RankEvaluator(Model& model, const RatingList& rlist, const RankEvaluatorConfig& config) :
	_model(model),
	_rlist(rlist),
	_config(config),
	_gtRank(rlist.numUser()) { }

template <class Model>
void RankEvaluator<Model>::evaluate() {
	computeGroundTruth();
	for (int n : _config.RANK_SIZE) {
		printf("Evaluate Ranking Top %d:\n", n);
		switch (_config.METHOD) {
		case RankEvaluatorConfig::METHOD_PRECISION:
			computePrecision(n);
			break;
		case RankEvaluatorConfig::METHOD_RECALL:
			computeRecall(n);
			break;
		case RankEvaluatorConfig::METHOD_F1:
			computeF1(n);
			break;
		default:
			break;
		}
	}
}

template <class Model>
void RankEvaluator<Model>::computeGroundTruth() {
	for (int i = 0; i < _rlist.numRating(); ++i) {
		const RatingRecord& rr = _rlist.get(i);
		RatingAndItemID rai;
		rai.rating = rr.rating();
		rai.itemID = rr.itemID();
		_gtRank[rr.userID()].add(rai);
	}
	QuickSorter qsort;
	for (int i = 0; i < _rlist.numUser(); ++i) {
		ArrayList<RatingAndItemID>& list = _gtRank[i];
		qsort(list.begin(), list.size(), [&](const RatingAndItemID& lhs, const RatingAndItemID& rhs)->int
			{ return (lhs.rating < rhs.rating)?1:-1; });
	}
}

template <class Model>
void RankEvaluator<Model>::computePrecision(int n) {
	for (int userID = 0; userID < _rlist.numUser(); ++userID) {
		ArrayList<int> ranklist = _model.recommendTopN(userID, n);
//		for ()
	}
}

template <class Model>
void RankEvaluator<Model>::computeRecall(int n) {

}

template <class Model>
void RankEvaluator<Model>::computeF1(int n) {

}

} //~ namespace ycg

#endif /* RANKEVALUATOR_H */
