#include "ItemBasedCFTest.h"
#include "../../time/Stopwatch.h"
#include "../../math/Math.h"
#include <cstdio>

namespace ycg {

ItemBasedCFTest::ItemBasedCFTest() {
//    movieLens = new MovieLens100K();
//    movieLens = new MovieLens1M();
//    movieLens = new MovieLens10M();
//	ratingArrayBase = new RatingRecord[movieLens->numRatingBase()];
//	ratingArrayTest = new RatingRecord[movieLens->numRatingTest()];
}

ItemBasedCFTest::~ItemBasedCFTest() {
//	delete []ratingArrayTest;
//	delete []ratingArrayBase;
//	delete movieLens;
}

void ItemBasedCFTest::run() {
//	printf(">>ItemBasedCFTest begin.\n");
//	printf("run item-based CF algorithm on %s dataset.\n", movieLens->name());
//	Stopwatch sw;
//	sw.start();
////    setupBaseAndTestFile();
//    for (int caseNo = 1; caseNo <= NUM_CASE; ++caseNo) {
//        printf("==========run case %d==========\n", caseNo);
//        loadData(caseNo);
//		printf("creating rating matrix...");
//        Stopwatch sw1;
//        sw1.start();
//        RatingMatrixStatic rms(movieLens->numUser(), movieLens->numItem(), movieLens->numRatingBase(), ratingArrayBase);
//        sw1.stop();
//        printf("done. Time cost = %dms\n", sw1.elapsedMilliseconds());
//        ItemBasedCFMT ibcf(rms, ItemBasedCF::SIM_ADJUSTED_COSINE, ItemBasedCF::MODEL_ALL, 50, ItemBasedCF::PRED_WEIGHTED_SUM);
//		train(ibcf);
//		test(ibcf);
//	}
//	sw.stop();
//	printf("%s done. Time cost = %dms\n", movieLens->name(), sw.elapsedMilliseconds());
//	printf(">>ItemBasedCFTest pass.\n");
}

void ItemBasedCFTest::setupBaseAndTestFile() {
//    double baseRatio = 0.8;
//    printf("setup base and test files(%d cases, x = %.2lf)...", NUM_CASE, baseRatio);
//	Stopwatch sw;
//	sw.start();
//    movieLens->setBaseRatio(baseRatio);
//    movieLens->splitRatingFile(NUM_CASE);
//    sw.stop();
//	printf("done. Time cost = %dms\n", sw.elapsedMilliseconds());
}

void ItemBasedCFTest::loadData(int caseNo) {
//    printf("loading data from file...");
//    Stopwatch sw;
//    sw.start();
//    movieLens->loadBaseRating(caseNo, ratingArrayBase);
//    movieLens->loadTestRating(caseNo, ratingArrayTest);
//    sw.stop();
//    printf("done. Time cost = %dms\n", sw.elapsedMilliseconds());
}

void ItemBasedCFTest::train(ItemBasedCF& ibcf) {
//	printf("training...");
//	Stopwatch sw;
//	sw.start();
//	ibcf.computeModel();
//	sw.stop();
//	printf("done. time cost = %dms\n", sw.elapsedMilliseconds());
}

void ItemBasedCFTest::test(ItemBasedCF& ibcf) {
//	printf("testing, compute MAE&RMSE...");
//	Stopwatch sw;
//	sw.start();
//	double MAE = 0.0;
//	double RMSE = 0.0;
//	for (int i = 0; i < movieLens->numRatingTest(); ++i) {
//		double groundTruth = ratingArrayTest[i].rating();
//		double predicted = ibcf.predictRating(ratingArrayTest[i].userID(), ratingArrayTest[i].itemID());
////		printf("%d pred = %lf, gt =  %lf\n", i, predicted, groundTruth);
//		MAE += Math::abs(predicted - groundTruth);
//		RMSE += Math::sqr(predicted - groundTruth);
//	}
//	MAE /= movieLens->numRatingTest();
//	RMSE /= movieLens->numRatingTest();
//	RMSE = Math::sqrt(RMSE);
//	sw.stop();
//	printf("done. time cost = %dms\n", sw.elapsedMilliseconds());
//	printf("MAE = %lf, RMSE = %lf\n", MAE, RMSE);
}

} //~ namespace ycg
