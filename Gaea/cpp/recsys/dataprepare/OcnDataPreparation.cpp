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
	auto rawFilenames = readRawFilenames();
	initMapping();
	for(String& inputFilename: rawFilenames) {
		String outputFilename = HOME_DIR + "\\session\\session"
				+ inputFilename.substring(inputFilename.indexOf('.') + 1);
		std::cout << "generating..." << outputFilename << std::endl;
		writeSessionDataOne(inputFilename, outputFilename);
	}
}

std::vector<String> OcnDataPreparation::readRawFilenames() {
	std::vector<String> filenames;
	Scanner scanner(HOME_DIR + "\\raw\\session_filelist.txt");
	while (scanner.hasNext()) {
		filenames.push_back(scanner.nextLine());
	}
	return filenames;
}

void OcnDataPreparation::initMapping() {
	macMap.clear();
	macCount = 0;
	assetMap.clear();
	assetCount = 0;
}

void OcnDataPreparation::writeSessionDataOne(const String& inputName, const String& outputName) {
	Scanner scanner(inputName);
	Writer writer(outputName);
	while (scanner.hasNext()) {
		String line = scanner.nextLine();
		if (line.startsWith("SQL>")) continue;
		auto fields = line.split2vector('|');
		String& mac = fields[0];
		String& asset = fields[4];
		String& start = fields[5];
		String& end = fields[6];
		if (asset.startsWith("AD")) continue;
		int macID = getMacID(mac);
		int assetID = getAssetID(asset);
		writer.print(macID).print(' ').print(assetID)
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
	String filename = HOME_DIR + "\\user\\user_id.txt";
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
	String filename = HOME_DIR + "\\video\\video_id.txt";
	Writer writer(filename);
	writer.println((int)assetVec.size());
	for (auto& p : assetVec) {
		writer.print(p.first).print(' ').println(p.second);
	}
}

} //~ namespace ycg
