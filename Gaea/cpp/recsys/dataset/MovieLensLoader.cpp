#include "MovieLensLoader.h"
#include "../../time/Stopwatch.h"
#include "../../util/Random.h"
#include <cassert>
#include <cstdio>

namespace ycg {

MovieLensLoader::MovieLensLoader(const MovieLensLoaderConfig &config) :
	_config(config) { }

MovieLensLoader::~MovieLensLoader() { }

RatingList MovieLensLoader::readTrainData() {
	const String& filename = _config.TRAIN_FILENAME;
	printf("MovieLensLoader::readTrainData(file = %s)...", filename.toChars());
	return readDataFile(filename);
}

RatingList MovieLensLoader::readTestData() {
	const String& filename = _config.TEST_FILENAME;
	printf("MovieLensLoader::readTestData(file = %s)...", filename.toChars());
	return readDataFile(filename);
}

RatingList MovieLensLoader::readDataFile(const String& filename) {
	Stopwatch sw;
	sw.start();
	FILE *fp = fopen(filename.toChars(), "r");
    assert(fp != nullptr);
    int numUser, numItem, numRating;
    fscanf(fp, "%d::%d::%d", &numUser, &numItem, &numRating);
    RatingList data(numUser, numItem, numRating, 1.0, 5.0);
    for (int i = 0; i < numRating; ++i) {
		int userID, itemID;
		double rating;
		fscanf(fp, "%d::%d::%lf", &userID, &itemID, &rating);
		data.add(RatingRecord(userID, itemID, rating));
    }
    fclose(fp);
	sw.stop();
	printf("done. Time = %dms\n", sw.elapsedMilliseconds());
	return data;
}

} //~ namespace ycg
