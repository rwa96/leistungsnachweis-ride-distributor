#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#define MAX_ROWS_SHOWN 10

using namespace boost::numeric::ublas;

template<typename T>
std::string matrixToString(matrix<T> mat){
    std::ostringstream result;

    unsigned iMax = mat.size1() > MAX_ROWS_SHOWN ? MAX_ROWS_SHOWN/2 : mat.size1();

    for(unsigned i = 0; i < iMax; ++i) {
        const matrix_row<matrix<T>> row(mat, i);
        for(unsigned j = 0; j < mat.size2(); ++j) {
            result << row(j) << ' ';
        }
        result << std::endl;
    }

    if(iMax != mat.size1()) {
        result << "[...]" << std::endl;

        for(unsigned i = mat.size1() - MAX_ROWS_SHOWN / 2; i < mat.size1(); ++i) {
            const matrix_row<matrix<T>> row(mat, i);
            for(unsigned j = 0; j < mat.size2(); ++j) {
                result << row(j) << ' ';
            }
            result << std::endl;
        }
    }

    return result.str();
}

#endif // UTILS_H
