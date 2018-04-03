#include <sstream>
#include "InputData.hpp"

InputData::InputData(const std::string path) throw(std::fstream::failure) {
	std::fstream inFile;
	inFile.exceptions(std::fstream::failbit | std::fstream::badbit);

	{ inFile.open(path, std::ios_base::in);
		inFile >> this->r >> this->c >> this->f >> this->n >> this->b >> this->t;

		this->rides = { this->n, 4 };
		//this->ride_distances = { this->n };

		for (int i = 0; i < this->n; i++) {
			inFile >> rides(i, 0) >> rides(i, 1) >> rides(i, 2) >> rides(i, 3);
		}
	}
};

std::string InputData::str() const {
	std::ostringstream result;

	result << "number of rides: " << this->n << std::endl;
	result << "map: (" << this->r << ", " << this->c << ")" << std::endl;
	result << "number of cars: " << this->f << std::endl;
	result << "bonus: " << this->b << std::endl;
	result << "simulation steps: " << this->t << std::endl;

	return result.str();
};
