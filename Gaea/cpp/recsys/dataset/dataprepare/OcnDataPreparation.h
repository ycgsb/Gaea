#ifndef OCNDATAPREPARATION_H_
#define OCNDATAPREPARATION_H_

#include <iostream>
#include <string>
#include <vector>

namespace ycg {

class OcnDataPreparation {
public:
	OcnDataPreparation();
	virtual ~OcnDataPreparation();
	void run();
private:
	void formatSessionData();
	void formatSessionFile(std::istream& is, std::ostream& os);
	std::vector<std::string> generateSessionFilenames();

private:
	static const std::string HOME_DIR;
};

} //~ namespace ycg

#endif /* OCNDATAPREPARATION_H_ */
