#ifndef RATINGEVALUATOR_H
#define RATINGEVALUATOR_H

#include "../util/RatingList.h"
#include "../../time/Stopwatch.h"
#include "../../math/Math.h"
#include <cstdio>

namespace ycg {

struct RatingEvaluatorConfig {
	enum Method {
		METHOD_MAE,
		METHOD_NMAE,
		METHOD_RMSE
	};
	Method METHOD;
};

template <class Model>
class RatingEvaluator {
public:
	RatingEvaluator(Model& model, const RatingList& rlist, const RatingEvaluatorConfig& config) :
		_model(model), _rlist(rlist), _config(config),
		_mae(0.0), _nmae(0.0), _rmse(0.0) { }
	virtual ~RatingEvaluator() { }
	void evaluate();
private:
	void evaluateMAE();
	void evaluateNMAE();
	void evaluateRMSE();
private:
	const RatingEvaluatorConfig& _config;
	const RatingList& _rlist;
	Model& _model;
	double _mae;
	double _nmae;
	double _rmse;
};

template <class Model>
void RatingEvaluator<Model>::evaluate() {
	switch (_config.METHOD) {
		case RatingEvaluatorConfig::METHOD_MAE:
			evaluateMAE();
			break;
		case RatingEvaluatorConfig::METHOD_NMAE:
			evaluateNMAE();
			break;
		case RatingEvaluatorConfig::METHOD_RMSE:
			evaluateRMSE();
			break;
		default:
			break;
	}
}

template <class Model>
void RatingEvaluator<Model>::evaluateMAE() {
	printf("RatingEvaluator::evaluateMAE...");
	Stopwatch sw;
	sw.start();
	_mae = 0.0;
	for (int i = 0; i < _rlist.numRating(); ++i) {
		const RatingRecord& rr = _rlist.get(i);
		double groundTruth = rr.rating();
		double predicted = _model.predictRating(rr.userID(), rr.itemID());
//		printf("pred = %lf, gt = %lf\n", predicted, groundTruth);
		_mae += Math::abs(predicted-groundTruth);
	}
	_mae /= _rlist.numRating();
	sw.stop();
	printf("done. Time = %dms\n", sw.elapsedMilliseconds());
	printf("MAE = %lf\n", _mae);
}

template <class Model>
void RatingEvaluator<Model>::evaluateNMAE() {
	printf("RatingEvaluator::evaluateNMAE...");
	Stopwatch sw;
	sw.start();
	_nmae = 0.0;
	for (int i = 0; i < _rlist.numRating(); ++i) {
		const RatingRecord& rr = _rlist.get(i);
		double groundTruth = rr.rating();
		double predicted = _model.predictRating(rr.userID(), rr.itemID());
//		printf("pred = %lf, gt = %lf\n", predicted, groundTruth);
		_nmae += Math::abs(predicted-groundTruth);
	}
	_nmae /= _rlist.numRating();
	_nmae /=  (_rlist.highestRating() - _rlist.lowestRating());
	sw.stop();
	printf("done. Time = %dms\n", sw.elapsedMilliseconds());
	printf("NMAE = %lf\n", _nmae);
}

template <class Model>
void RatingEvaluator<Model>::evaluateRMSE() {
	printf("RatingEvaluator::evaluateRMSE...");
	Stopwatch sw;
	sw.start();
	_rmse = 0.0;
	for (int i = 0; i < _rlist.numRating(); ++i) {
		const RatingRecord& rr = _rlist.get(i);
		double groundTruth = rr.rating();
		double predicted = _model.predictRating(rr.userID(), rr.itemID());
		_rmse += Math::sqr(predicted-groundTruth);
	}
	_rmse /= _rlist.numRating();
	_rmse = Math::sqrt(_rmse);
	sw.stop();
	printf("done. Time = %dms\n", sw.elapsedMilliseconds());
	printf("RMSE = %lf\n", _rmse);
}

} //~ namespace ycg

#endif /* RATINGEVALUATOR_H */
