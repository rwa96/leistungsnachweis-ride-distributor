#ifndef TENSOR_H
#define TENSOR_H

#include <string>
#include <memory>
#include <initializer_list>
#include <vector>
#include <sstream>
#include <algorithm>

#define MAX_SHOWN_ENTRIES (unsigned)20


template<typename T>
class Tensor{
public:

    Tensor():size(0){};

    Tensor(std::initializer_list<unsigned> args):dims(args){
        size = 1;
        for(auto& dim: dims){
            size *= dim;
        }
        if(size == 0){
            dims.clear();
        }
        data = std::make_unique<T[]>(size);
    };

    std::string str() const{
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

    inline T& operator()(const int x)
    {return data[x];};

    inline T& operator()(const int x, const int y)
    {return data[x*dims[1] + y];};

    inline T& operator()(const int x, const int y, const int z)
    {return data[x*dims[1]*dims[2] + y*dims[2] + z];};

    inline const unsigned getSize() const
    {return size;};

    const std::vector<unsigned> getDims() const
    {return dims;};

private:

    unsigned size;
    std::vector<unsigned> dims;
    std::unique_ptr<T[]> data;

};

#endif // TENSOR_H
