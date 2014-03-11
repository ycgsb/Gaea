#ifndef MOVIELENSLOADER_H
#define MOVIELENSLOADER_H

#include "../util/RatingList.h"
#include "../../lang/String.h"

namespace ycg {

struct MovieLensLoaderConfig {
	String TRAIN_FILENAME;
	String TEST_FILENAME;
};

class MovieLensLoader {
public:
	MovieLensLoader(const MovieLensLoaderConfig& config);
	virtual ~MovieLensLoader();
	RatingList readTrainData();
	RatingList readTestData();
private:
	RatingList readDataFile(const String& filename);
private:
	const MovieLensLoaderConfig& _config;
};

class MovieLensAbstract {
public:
	MovieLensAbstract(int numUser, int numItem, int numRating);
	virtual ~MovieLensAbstract();
	int numUser() const { return _numUser; }
	int numItem() const { return _numItem; }
	int numRating() const { return _numRating; }
	int numRatingBase() const { return _numRatingBase; }
	int numRatingTest() const { return _numRatingTest; }
	double baseRatio() const { return _baseRatio; }
	void setBaseRatio(double baseRatio);
	void loadAllRating(RatingRecord *ratingArray);
	void loadBaseRating(int caseNo, RatingRecord *ratingArray);
	void loadTestRating(int caseNo, RatingRecord *ratingArray);
	void splitRatingFile(int numCase);
	virtual const char* name() const = 0;
protected:
    virtual String allRatingFileName() = 0;
    virtual String baseRatingFileName(int caseNo) = 0;
    virtual String testRatingFileName(int caseNo) = 0;
	virtual void loadRatingFile(const String& fileName, RatingRecord *ratingArray, int numRating);
	virtual void saveRatingFile(const String& fileName, const RatingRecord *ratingArray, int numRating);
protected:
	const int _numUser;
	const int _numItem;
	const int _numRating;
	int _numRatingBase;
	int _numRatingTest;
	double _baseRatio;
};

class MovieLens100K : public MovieLensAbstract {
public:
	MovieLens100K();
	~MovieLens100K();
	const char* name() const;
protected:
	String allRatingFileName();
	String baseRatingFileName(int caseNo);
	String testRatingFileName(int caseNo);
private:
	static const String DATASET_HOME;
};

class MovieLens1M : public MovieLensAbstract {
public:
	MovieLens1M();
	~MovieLens1M();
	const char* name() const;
protected:
	String allRatingFileName();
	String baseRatingFileName(int caseNo);
	String testRatingFileName(int caseNo);
private:
	static const String DATASET_HOME;
};

class MovieLens10M : public MovieLensAbstract {
public:
	MovieLens10M();
	~MovieLens10M();
	const char* name() const;
protected:
	String allRatingFileName();
	String baseRatingFileName(int caseNo);
	String testRatingFileName(int caseNo);
private:
	static const String DATASET_HOME;
};

} //~ namespace ycg

#endif /* MOVIELENSLOADER_H */
