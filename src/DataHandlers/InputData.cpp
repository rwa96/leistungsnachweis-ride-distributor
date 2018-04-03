#include <sstream>
#include "InputData.hpp"
#include "Utils.hpp"

InputData::InputData(const std::string path){
	std::fstream inFile;
	inFile.exceptions(std::fstream::failbit | std::fstream::badbit);

	{ inFile.open(path, std::ios_base::in);
		inFile >> r >> c >> f >> n >> b >> t;

		rides = matrix<unsigned short>(n, 4);
		ride_distances = vector<unsigned short>(n);

		for (unsigned i = 0; i < n; i++) {
			inFile >> rides(i, 0) >> rides(i, 1) >> rides(i, 2) >> rides(i, 3);
		}
	} // inFile closes
};

std::string InputData::str() const {
	std::ostringstream result;

	result << "number of rides: " << n << std::endl;
	result << "map: (" << r << ", " << c << ")" << std::endl;
	result << "number of cars: " << f << std::endl;
	result << "bonus: " << b << std::endl;
	result << "simulation steps: " << t << std::endl;
    result << "rides:" << std::endl << matrixToString(rides) << std::endl;

	return result.str();
};
