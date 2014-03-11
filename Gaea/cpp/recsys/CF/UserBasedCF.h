#ifndef USERBASEDCF_H
#define USERBASEDCF_H

#include "MemoryBasedCF.h"
#include "../util/RatingList.h"
#include "../util/RatingMatSparse.h"

namespace ycg {

struct UserBasedConfig {
	enum SimType {
		PEARSON, COSINE, ADJUST_COSINE, MSE
	};
	enum ModelType {
		ALL, NEAREST_K
	};
	SimType SIM_TYPE;
	ModelType MODEL_TYPE;
	int NUM_NEIGHBOUR;
	int MIN_BOTH_RATED_ITEM_NUM;
	int NUM_THREAD;
};

class UserBasedCF : public MemoryBasedCF {
public:
	UserBasedCF(const RatingList& rlist, const UserBasedConfig& config);
	virtual ~UserBasedCF();
	void train();
	double predictRating(int userID, int itemID);
protected:
	virtual void computeAllUserSim();
	virtual void computeAllUserNearestK();
	double computeUserSim(int userID1, int userID2, double *vec1, double *vec2);
	void computeUserNearestK(int userID, double *vec);
	double predictWeightedSum(int userID, int itemID, double simThreshold);
	void createUserSimMat();
	void freeUserSimMat();
protected:
	const UserBasedConfig& _config;
	double **_userSimMat;
	double *_userAverage;
	double *_userSimThreshold;
};

class UserBasedCFMT : public UserBasedCF {
public:
	UserBasedCFMT(const RatingList& rlist, const UserBasedConfig& config) :
		UserBasedCF(rlist, config) { }
protected:
	class ComputeAllUserSimRunner {
	public:
		ComputeAllUserSimRunner(UserBasedCFMT& ubcf):_ubcf(ubcf) {}
		void operator() (int threadID);
	private:
		UserBasedCFMT& _ubcf;
	};
    class ComputeAllUserNearestKRunner {
    public:
		ComputeAllUserNearestKRunner(UserBasedCFMT& ubcf):_ubcf(ubcf) {}
	    void operator() (int threadID);
    private:
	    UserBasedCFMT& _ubcf;
    };
    friend class ComputeAllUserSimRunner;
    friend class ComputeAllUserNearestKRunner;
	void computeAllUserSim();
	void computeAllUserNearestK();
};

} //~ namespace ycg

#endif /* USERBASEDCF_H */
