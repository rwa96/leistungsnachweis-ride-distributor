#ifndef GENERATOR_H
#define GENERATOR_H

#include "Types.hpp"
#include "Tensor.hpp"
#include "InputData.hpp"

class Generator {
public:

    Generator(InputData& inputData, unsigned expandSize, unsigned nTries, unsigned kBest) :
        inputData(inputData), expandSize(expandSize), nTries(nTries), kBest(kBest) {};

    void generate(Types::Choices& output, std::vector<int>& unassigned,
                  std::unique_ptr<Types::CarData> cars);

private:

    void selectFromSearchSpace(Types::Choices& output, Tensor<int>& finishTimes,
                               Tensor<int>& finishPoints, std::vector<int>& unassigned,
                               std::unique_ptr<Types::CarData>& cars);
    void createSearchSpace(Tensor<int>& finishTimes, Tensor<int>& finishPoints,
                           std::vector<int>& unassigned, std::unique_ptr<Types::CarData>& cars);

    InputData& inputData;
    unsigned expandSize, nTries, kBest;

};

#endif // GENERATOR_H
