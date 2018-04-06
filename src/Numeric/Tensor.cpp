#include <sstream>
#include "Tensor.hpp"


Tensor::Tensor(std::initializer_list<unsigned> args):dims(args){
    size = 1;
    for(auto& dim: dims){
        size *= dim;
    }
    if(size == 0){
        dims.clear();
    }
    data = std::make_unique<int[]>(size);
};


std::string Tensor::str() const{
    std::ostringstream result;

    result << '[';
    for(unsigned i = 0; i < size; ++i){
        result << data[i];
        if(i < size-1){result << ", ";}
    }
    result << ']' << std::endl;

    return result.str();
};
