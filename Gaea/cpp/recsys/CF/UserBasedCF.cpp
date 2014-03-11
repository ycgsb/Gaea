#include "UserBasedCF.h"
#include "../util/RatingUtil.h"
#include "../../math/Math.h"
#include "../../math/Statistic.h"
#include "../../algorithms/sort/RandomizedSelector.h"
#include "../../time/Stopwatch.h"
#include <thread>
#include <cstdio>

namespace ycg {

UserBasedCF::UserBasedCF(const RatingList& rlist, const UserBasedConfig& config) :
	MemoryBasedCF(rlist),
	_config(config),
	_userAverage(nullptr),
	_userSimThreshold(nullptr) {
	createUserSimMat();
	_userAverage = new double[_ratingMS.numUser()];
	if (_config.MODEL_TYPE == UserBasedConfig::ModelType::NEAREST_K) {
		_userSimThreshold = new double[_ratingMS.numUser()];
	}
}

UserBasedCF::~UserBasedCF() {
	delete []_userSimThreshold;
	delete []_userAverage;
	freeUserSimMat();
}

void UserBasedCF::createUserSimMat() {
	_userSimMat = new double*[_ratingMS.numUser()];
	for (int i = 0; i < _ratingMS.numUser(); ++i) {
		_userSimMat[i] = new double[_ratingMS.numUser()];
	}
}

void UserBasedCF::freeUserSimMat() {
	for (int i = 0; i < _ratingMS.numUser(); ++i) {
		delete []_userSimMat[i];
	}
	delete []_userSimMat;
}

void UserBasedCF::train() {
	printf("UserBasedCF::train...");
	Stopwatch sw;
	sw.start();
	RatingUtil::computeUserAverage(_ratingMS, _userAverage);
	computeAllUserSim();
	if (_config.MODEL_TYPE == UserBasedConfig::ModelType::NEAREST_K) {
		computeAllUserNearestK();
	}
	printf("done. Time = %dms.\n", sw.stop().elapsedMilliseconds());
}

void UserBasedCF::computeAllUserSim() {
	double *array1 = new double[_ratingMS.numItem()];
	double *array2 = new double[_ratingMS.numItem()];
	for (int i = 0; i < _ratingMS.numUser(); ++i) {
		_userSimMat[i][i] = 1.0;
		for (int j = i + 1; j < _ratingMS.numUser(); ++j) {
			_userSimMat[i][j] = _userSimMat[j][i]
			                  = computeUserSim(i, j, array1, array2);
		}
	}
	delete []array1;
	delete []array2;
}

double UserBasedCF::computeUserSim(int userID1, int userID2, double *vec1, double *vec2) {
	int bothCnt = 0;
	auto iter1 = _ratingMS.beginRow(userID1);
	auto end1 = _ratingMS.endRow(userID1);
	auto iter2 = _ratingMS.beginRow(userID2);
	auto end2 = _ratingMS.endRow(userID2);
	while (iter1 != end1 && iter2 != end2) {
		const RatingRecord r1 = *iter1;
		const RatingRecord r2 = *iter2;
		if (r1.itemID() == r2.itemID()) {
			vec1[bothCnt] = r1.rating();
			vec2[bothCnt] = r2.rating();
			++bothCnt;
			++iter1; ++iter2;
		} else if (r1.itemID() < r2.itemID()) {
			++iter1;
		} else if (r1.itemID() > r2.itemID()) {
			++iter2;
		}
	}
	double sim = 0.0;
	if (bothCnt >= _config.MIN_BOTH_RATED_ITEM_NUM) {
		switch (_config.SIM_TYPE) {
		case UserBasedConfig::SimType::PEARSON:
			sim = Statistic::pearsonCorrelation(vec1, vec2, bothCnt);
			break;
		case UserBasedConfig::SimType::COSINE:
			sim = Statistic::cosineCorrelation(vec1, vec2, bothCnt);
			break;
		case UserBasedConfig::SimType::MSE:
			sim = Statistic::meanSquareError(vec1, vec2, bothCnt);
			break;
		default:
			break;
		}
	}
	return sim;
}

void UserBasedCF::computeAllUserNearestK() {
	double *array = new double[_ratingMS.numUser()];
	for (int i = 0; i < _ratingMS.numUser(); ++i) {
		computeUserNearestK(i, array);
	}
	delete []array;
}

void UserBasedCF::computeUserNearestK(int userID, double *vec) {
	for (int i = 0; i < _ratingMS.numUser(); ++i) {
		vec[i] = _userSimMat[userID][i];
	}
	RandomizedSelector<double> select;
	double th = select(vec, _ratingMS.numUser(), _config.NUM_NEIGHBOUR,
			[&](const double& a, const double& b){ return (a<b)?1:-1;});
	_userSimThreshold[userID] = Math::max(0.0, th);
}

double UserBasedCF::predictRating(int userID, int itemID) {
	if (_config.MODEL_TYPE == UserBasedConfig::ModelType::ALL) {
		return predictWeightedSum(userID, itemID, 0.0);
	} else if (_config.MODEL_TYPE == UserBasedConfig::ModelType::NEAREST_K) {
		return predictWeightedSum(userID, itemID, _userSimThreshold[userID]);
	} else {
		return 0.0;
	}
}

double UserBasedCF::predictWeightedSum(int userID, int itemID, double simThreshold) {
	double sum = 0.0, norm = 0.0;
	for (auto iter = _ratingMS.beginCol(itemID), end = _ratingMS.endCol(itemID);
			iter != end; ++iter) {
		const RatingRecord r = *iter;
		double sim = _userSimMat[userID][r.userID()];
		if (sim > simThreshold) {
			sum += sim * (r.rating()-_userAverage[r.userID()]);
			norm += sim;
		}
	}
	double bias = sum / (norm + 1e-200);
	double predRating = bias + _userAverage[userID];
	return predRating;
}

void UserBasedCFMT::computeAllUserSim() {
	int nthread = _config.NUM_THREAD;
	std::thread **threads = new std::thread*[nthread];
	for (int i = 0; i < nthread; ++i) {
		ComputeAllUserSimRunner runner(*this);
		threads[i] = new std::thread(runner, i);
	}
	for (int i = 0; i < nthread; ++i) {
		threads[i]->join();
		delete threads[i];
	}
    delete []threads;
}

void UserBasedCFMT::computeAllUserNearestK() {
	int nthread = _config.NUM_THREAD;
	std::thread **threads = new std::thread*[nthread];
	for (int i = 0; i < nthread; ++i) {
		ComputeAllUserNearestKRunner runner(*this);
		threads[i] = new std::thread(runner, i);
	}
	for (int i = 0; i < nthread; ++i) {
		threads[i]->join();
		delete threads[i];
	}
	delete []threads;
}

void UserBasedCFMT::ComputeAllUserSimRunner::operator () (int threadID) {
	double *array1 = new double[_ubcf._ratingMS.numItem()];
	double *array2 = new double[_ubcf._ratingMS.numItem()];
    int nthread = _ubcf._config.NUM_THREAD;
	int numUser = _ubcf._ratingMS.numUser();
	int total = numUser * (numUser - 1) / 2;
    int work = total / nthread;
    int begin = threadID * work;
    int end = (threadID != nthread-1) ? (begin+work) : total;
    for (int id = begin; id < end; ++id) {
        int x = static_cast<int>((sqrt(8.0*id+1)+1)/2);
        int y = id - x*(x-1)/2;
        _ubcf._userSimMat[x][y] = _ubcf._userSimMat[y][x]
             = _ubcf.computeUserSim(x, y, array1, array2);
    }
	delete []array1;
	delete []array2;
}

void UserBasedCFMT::ComputeAllUserNearestKRunner::operator () (int threadID) {
	int nthread = _ubcf._config.NUM_THREAD;
	int numUser = _ubcf._ratingMS.numUser();
	double *array = new double[_ubcf._ratingMS.numUser()];
	int total = numUser;
	int work = total / nthread;
	int begin = threadID*work;
	int end = (threadID != nthread-1) ? (begin + work) : total;
	for (int uid = begin; uid < end; ++uid) {
		_ubcf.computeUserNearestK(uid, array);
	}
	delete []array;
}


} //~ namespace ycg
