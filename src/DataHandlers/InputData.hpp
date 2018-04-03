#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <fstream>
#include <boost/numeric/ublas/matrix.hpp>
#include <string>

using namespace boost::numeric::ublas;

class InputData{
private:

    matrix<unsigned short> rides;
    vector<unsigned short> ride_distances;
    unsigned short r, c, f, n, b, t;

public:

    InputData(const std::string path) throw(std::fstream::failure);
	std::string str() const;

};

#endif // INPUTDATA_H
