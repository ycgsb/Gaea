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
	void initMapping();
	void writeSessionDataOne(const String& inputName, const String& outputNameSession);
	void writeMacMappingData();
	void writeAssetMapingData();
	std::vector<String> readRawFilenames();
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
