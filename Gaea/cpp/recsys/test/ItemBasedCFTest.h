#ifndef ITEMBASEDCFTEST_H
#define ITEMBASEDCFTEST_H

#include "../../test/Test.h"
#include "../dataset/MovieLensLoader.h"
#include "../util/RatingMatrixStatic.h"
#include "../CF/ItemBasedCF.h"
#include "../CF/ItemBasedCFMT.h"

namespace ycg {

class ItemBasedCFTest : public Test {
public:
	ItemBasedCFTest();
	~ItemBasedCFTest();
	void run();
	void run2();
private:
    void setupBaseAndTestFile();
    void loadData(int caseNo);
	void train(ItemBasedCF& ibcf);
	void test(ItemBasedCF& ibcf);
private:
    static const int NUM_CASE = 5;
	MovieLensAbstract *movieLens;
	RatingRecord *ratingArrayBase;
	RatingRecord *ratingArrayTest;
};

} //~ namespace ycg

#endif /* ITEMBASEDCFTEST_H */
