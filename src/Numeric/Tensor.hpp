#ifndef TENSOR_H
#define TENSOR_H

#include <string>
#include <memory>

class Tensor{
public:

    Tensor():rows(0), cols(0){};

    Tensor(const unsigned len);

    Tensor(const unsigned rows, const unsigned cols);

    std::string str() const;

    int& operator()(const int rows, const int cols);

    int& operator()(const int cols);

private:

    unsigned rows, cols;
    std::unique_ptr<int[]> data;

};

#endif // TENSOR_H
