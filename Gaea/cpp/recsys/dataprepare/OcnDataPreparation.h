#ifndef OCNDATAPREPARATION_H_
#define OCNDATAPREPARATION_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace ycg {

class OcnDataPreparation {
public:
	void run();
private:
	void formatSessionData();
	void formatSessionData(std::istream& is, std::ostream& os);
	void generateMacMappingData();
	void generateAssetMapingData();
	std::vector<std::string> generateDateNames();
	std::string makeDateString(int year, int month, int day);
	std::vector<std::string> extractFields(const std::string& line);
	std::string trimString(std::string& str);
private:
	static const std::string HOME_DIR;
	std::map<std::string, int> macMap;
	int macCount;
	std::map<std::string, int> assetMap;
	int assetCount;
};

} //~ namespace ycg

#endif /* OCNDATAPREPARATION_H_ */
