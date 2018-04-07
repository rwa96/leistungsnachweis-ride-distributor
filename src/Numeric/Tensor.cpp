#include <sstream>
#include <algorithm>
#include "Tensor.hpp"

#define MAX_SHOWN_ENTRIES (unsigned)20


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
    for(unsigned i = 0; i < std::min(size, MAX_SHOWN_ENTRIES); ++i){
        result << data[i];
        if(i < size-1){result << ", ";}
        else if(size > MAX_SHOWN_ENTRIES){result << "...";}
    }
    result << ']' << std::endl;

    return result.str();
};
