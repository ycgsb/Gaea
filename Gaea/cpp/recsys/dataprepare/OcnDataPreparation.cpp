#include "OcnDataPreparation.h"
#include "../../io/Scanner.h"
#include "../../io/Writer.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <algorithm>

namespace ycg {

const String OcnDataPreparation::HOME_DIR = "E:\\Dataset\\Ocn";

void OcnDataPreparation::run() {
	writeSessionDataAll();
	writeMacMappingData();
	writeAssetMapingData();
}

void OcnDataPreparation::writeSessionDataAll() {
	auto datenames = generateDateNames();
	macMap.clear();	macCount = 0;
	assetMap.clear(); assetCount = 0;
	for(std::string& date: datenames) {
		String inputFilename = HOME_DIR + "\\Raw\\Session\\ow_rental_sitv." + date + ".txt";
		String outputFilename1 = HOME_DIR + "\\session\\session" + date + ".txt";
		String outputFilename2 = HOME_DIR + "\\session\\ad\\ad" + date + ".txt";
		std::cout << "processing " << date << std::endl;
		writeSessionDataOne(inputFilename, outputFilename1, outputFilename2);
	}
}

std::vector<std::string> OcnDataPreparation::generateDateNames() {
	static const int dayInMonth[12] = {31, 28, 31, 30, 31, 30,
									   31, 31, 30, 31, 30, 31};
	std::vector<std::string> datenames;
	int year = 2013, month, day;
	for (month = 1; month <= 12; ++month) {
		for (day = 1; day <= dayInMonth[month-1]; ++day) {
			datenames.push_back(date2string(year, month, day));
		}
	}
	year = 2014; month = 1;
	for (day = 1; day <= 7; ++day) {
		datenames.push_back(date2string(year, month, day));
	}
	return datenames;
}

std::string OcnDataPreparation::date2string(int year, int month, int day) {
	std::ostringstream oss;
	oss << year << std::setfill('0')
		<< std::setw(2) << month
		<< std::setw(2) << day;
	return oss.str();
}

void OcnDataPreparation::writeSessionDataOne(const String& inputName, const String& outputNameSession, const String& outputNameAd) {
	Scanner scanner(inputName);
	Writer writerSession(outputNameSession);
	Writer writerAd(outputNameAd);
	while (scanner.hasNext()) {
		String line = scanner.nextLine();
		if (line.startsWith("SQL>")) continue;
		auto fields = line.split2vector('|');
		String& mac = fields[0];
		String& asset = fields[4];
		String& start = fields[5];
		String& end = fields[6];
		if (asset.startsWith("AD")) {
			writerAd.print(mac).print('|').print(asset)
					.print('|').print(start).print('|')
					.println(end);
			continue;
		}
		int macID = getMacID(mac);
		int assetID = getAssetID(asset);
		writerSession.print(macID).print(' ').print(assetID)
			.print(' ').print(start.trim().replace(' ', 'T'))
			.print(' ').println(end.trim().replace(' ', 'T'));
	}
}

int OcnDataPreparation::getMacID(const String& mac) {
	auto ret = macMap.insert(std::make_pair(mac, macCount));
	if (ret.second == true) {
		return macCount++;
	} else {
		return ret.first->second;
	}
}

int OcnDataPreparation::getAssetID(const String& asset) {
	auto ret = assetMap.insert(std::make_pair(asset, assetCount));
	if (ret.second == true) {
		return assetCount++;
	} else {
		return ret.first->second;
	}
}

void OcnDataPreparation::writeMacMappingData() {
	std::vector<std::pair<int, String>> macVec;
	for(auto iter = macMap.begin(), end = macMap.end(); iter != end; ++iter) {
		const String& mac = iter->first;
		int id = iter->second;
		macVec.push_back(std::make_pair(id, mac));
	}
	std::sort(macVec.begin(), macVec.end());
	String filename = HOME_DIR + "\\user\\mac_id.txt";
	Writer writer(filename);
	writer.println((int)macVec.size());
	for (const auto& p : macVec) {
		writer.print(p.first).print(' ').println(p.second);
	}
}

void OcnDataPreparation::writeAssetMapingData() {
	std::vector<std::pair<int, String>> assetVec;
	for(auto iter = assetMap.begin(), end = assetMap.end(); iter != end; ++iter) {
		const String& asset = iter->first;
		int id = iter->second;
		assetVec.push_back(std::make_pair(id, asset));
	}
	std::sort(assetVec.begin(), assetVec.end());
	String filename = HOME_DIR + "\\video\\asset_id.txt";
	Writer writer(filename);
	writer.println((int)assetVec.size());
	for (auto& p : assetVec) {
		writer.print(p.first).print(' ').println(p.second);
	}
}

} //~ namespace ycg
