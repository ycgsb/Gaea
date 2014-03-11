#include "RecSysLauncher.h"
#include "dataset/MovieLensLoader.h"
#include "dataset/JesterLoader.h"
#include "dataset/NetflixLoader.h"
#include "util/RatingMatSparse.h"
#include "CF/UserBasedCF.h"
#include "CF/POP.h"
#include "evaluation/RatingEvaluator.h"
#include "evaluation/RankEvaluator.h"
#include "RecSysExperiment.h"

namespace ycg {

RecSysLauncher::RecSysLauncher() { }

RecSysLauncher::~RecSysLauncher() { }

void RecSysLauncher::launch() {
	MovieLensLoaderConfig ldcfg;
	POPConfig popcfg;
	UserBasedConfig ubcfg;
	RankEvaluatorConfig evalcfg;
	ldcfg.TRAIN_FILENAME = "D:\\Research\\Recsys\\Dataset\\MovieLens\\ml-1m\\my\\ratings1.base";
	ldcfg.TEST_FILENAME = "D:\\Research\\Recsys\\Dataset\\MovieLens\\ml-1m\\my\\ratings1.test";
	popcfg.PRED_METHOD = POPConfig::PRED_ITEM_AVERAGE;
	popcfg.RANK_METHOD = POPConfig::RANK_RANDOM;
	ubcfg.SIM_TYPE = UserBasedConfig::SimType::PEARSON;
	ubcfg.MODEL_TYPE = UserBasedConfig::ModelType::NEAREST_K;
	ubcfg.MIN_BOTH_RATED_ITEM_NUM = 15;
	ubcfg.NUM_NEIGHBOUR = 200;
	ubcfg.NUM_THREAD = 16;
	evalcfg.METHOD = RankEvaluatorConfig::METHOD_PRECISION;
	evalcfg.RANK_SIZE.add(10).add(20).add(30).add(40).add(50).add(100).add(200).add(500).add(1000);
	RecSysExperiment<MovieLensLoader, MovieLensLoaderConfig, RatingList,
					POP, POPConfig,
					RankEvaluator<POP>, RankEvaluatorConfig> exp(ldcfg, popcfg, evalcfg);
	exp.perform();
}

} //~ namespace ycg
