#include <sstream>
#include "Tensor.hpp"

Tensor::Tensor(const unsigned len):rows(1),
                                   cols(len){
    data = std::make_unique<int[]>(len);
};

Tensor::Tensor(const unsigned rows, const unsigned cols):rows(rows),
                                                         cols(cols){
    data = std::make_unique<int[]>(rows*cols);
};

std::string Tensor::str() const{
    std::ostringstream result;

    for(unsigned r = 0; r < rows; ++r){
        for(unsigned c = 0; c < cols; ++c){
            result << data[r*cols + c] << ' ';
        }
        result << std::endl;
    }

    return result.str();
};

int& Tensor::operator()(const int row, const int col){
    return data[row*cols + col];
};

int& Tensor::operator()(const int cols){
    return data[cols];
};
