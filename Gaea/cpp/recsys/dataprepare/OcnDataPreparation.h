#ifndef OCNDATAPREPARATION_H
#define OCNDATAPREPARATION_H

#include "../../lang/String.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace ycg {

class OcnDataPreparation {
public:
	void run();
private:
	void writeSessionDataAll();
	void writeSessionDataOne(const String& inputName, const String& outputNameSession,
			const String& outputNameAd);
	void writeMacMappingData();
	void writeAssetMapingData();
	std::vector<std::string> generateDateNames();
	std::string date2string(int year, int month, int day);
	int getMacID(const String& mac);
	int getAssetID(const String& asset);
private:
	static const String HOME_DIR;
	std::map<String, int> macMap;
	int macCount;
	std::map<String, int> assetMap;
	int assetCount;
};

} //~ namespace ycg

#endif /* OCNDATAPREPARATION_H */
