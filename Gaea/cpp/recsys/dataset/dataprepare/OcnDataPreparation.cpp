#include "OcnDataPreparation.h"

namespace ycg {

const std::string OcnDataPreparation::HOME_DIR = "E:\\Dataset\\Ocn";

OcnDataPreparation::OcnDataPreparation() { }

OcnDataPreparation::~OcnDataPreparation() { }

void OcnDataPreparation::run() {
	formatSessionData();
}

void OcnDataPreparation::formatSessionData() {
}

void OcnDataPreparation::formatSessionFile(std::istream& is, std::ostream& os) {
}

std::vector<std::string> OcnDataPreparation::generateSessionFilenames() {
	std::vector<std::string> filenames;
	for (int month = 0; month < 12; ++month) {

	}
	return filenames;
}

} //~ namespace ycg
