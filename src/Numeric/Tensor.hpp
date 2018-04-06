#ifndef TENSOR_H
#define TENSOR_H

#include <string>
#include <memory>
#include <initializer_list>
#include <vector>


class Tensor{
public:

    Tensor():size(0){};

    Tensor(std::initializer_list<unsigned>);

    std::string str() const;

    inline int& operator()(const int x)
    {return data[x];};

    inline int& operator()(const int x, const int y)
    {return data[x*dims[1] + y];};

    inline int& operator()(const int x, const int y, const int z)
    {return data[x*dims[1]*dims[2] + y*dims[2] + z];};

    const unsigned getSize() const {return size;};

    const std::vector<unsigned> getDims() const {return dims;};

private:

    unsigned size;
    std::vector<unsigned> dims;
    std::unique_ptr<int[]> data;

};

#endif // TENSOR_H
