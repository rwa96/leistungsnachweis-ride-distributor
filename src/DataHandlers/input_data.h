#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <boost/numeric/ublas/matrix.hpp>
#include <string>

using namespace boost::numeric::ublas;

class InputData{
private:

    const matrix<unsigned short> rides;
    const vector<unsigned short> ride_distances;
    unsigned short r, c, f, n, b, t;

public:

    InputData(const std::string path);

};

#endif // INPUTDATA_H
