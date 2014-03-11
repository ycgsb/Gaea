#include "OcnDataPreparation.h"
#include <fstream>
#include <sstream>
#include <iomanip>

namespace ycg {

const std::string OcnDataPreparation::HOME_DIR = "E:\\Dataset\\Ocn";

void OcnDataPreparation::run() {
	formatSessionData();
}

void OcnDataPreparation::formatSessionData() {
	auto datenames = generateDateNames();
	macMap.clear();	macCount = 0;
	assetMap.clear(); assetCount = 0;
	for(std::string& date: datenames) {
		std::string inputFilename = HOME_DIR + "\\Raw\\Session\\ow_rental_sitv." + date + ".txt";
		std::string outputFilename = HOME_DIR + "\\session\\session" + date + ".txt";
		std::ifstream fis(inputFilename);
		std::ofstream fos(outputFilename);
		std::cout << "generating " << outputFilename << "..." << std::endl;
		formatSessionData(fis, fos);
		break;
	}
}

std::vector<std::string> OcnDataPreparation::generateDateNames() {
	std::vector<std::string> datenames;
	int dayInMonth[12] = {31, 28, 31, 30, 31, 30,
						  31, 31, 30, 31, 30, 31};
	int year = 2013, month, day;
	for (month = 1; month <= 12; ++month) {
		for (day = 1; day <= dayInMonth[month-1]; ++day) {
			datenames.push_back(makeDateString(year, month, day));
		}
	}
	year = 2014; month = 1;
	for (day = 1; day <= 7; ++day) {
		datenames.push_back(makeDateString(year, month, day));
	}
	return datenames;
}

std::string OcnDataPreparation::makeDateString(int year, int month, int day) {
	std::ostringstream oss;
	oss << year << std::setfill('0')
		<< std::setw(2) << month
		<< std::setw(2) << day;
	return oss.str();
}

void OcnDataPreparation::formatSessionData(std::istream& is, std::ostream& os) {
	std::string line;
	while (std::getline(is, line)) {
		if (line.substr(0, 4) == "SQL>") continue;
		auto fields = extractFields(line);
		std::string& mac = fields[0];
		auto& asset = fields[4];
		auto& start = fields[5];
		auto& end = fields[6];
		std::cout << mac << std::endl;
		std::cout << asset << std::endl;
		std::cout << start << std::endl;
		std::cout << end << std::endl;
	}
	os << "tmp";
}

void OcnDataPreparation::generateMacMappingData() {
}

void OcnDataPreparation::generateAssetMapingData() {
}

std::vector<std::string> OcnDataPreparation::extractFields(
		const std::string& line) {
	std::vector<std::string> fields;
	std::string::size_type pos1 = 0, pos2 = 0;
	while ((pos2 = line.find('|', pos1)) != std::string::npos) {
		fields.push_back(trimString(line.substr(pos1, pos2 - pos1)));
		pos1 = pos2 + 1;
	}
	fields.push_back(trimString(line.substr(pos1)));
	return fields;
}

std::string OcnDataPreparation::trimString(std::string& str) {
	if (str.empty()) {
		return str;
    }
	str.erase(0, str.find_first_not_of(" \t"));
	str.erase(str.find_last_not_of(" \t") + 1);
    return str;
}

} //~ namespace ycg
