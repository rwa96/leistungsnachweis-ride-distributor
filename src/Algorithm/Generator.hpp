#ifndef GENERATOR_H
#define GENERATOR_H

#include <random>
#include "Types.hpp"
#include "Tensor.hpp"
#include "InputData.hpp"
#include "SearchGraphNode.hpp"

class Generator {
public:

    Generator(InputData& inputData, unsigned nTries, unsigned kBest) :
        inputData(inputData), nTries(nTries), kBest(kBest) {};

    void generate(Types::Choices& output, std::shared_ptr<SearchGraphNode>& prevNode,
                  std::vector<int>& unassigned,
                  std::unique_ptr<Types::CarData> cars);

private:

    void selectFromSearchSpace(Types::Choices& output,
                               std::shared_ptr<SearchGraphNode>& prevNode, Tensor<int>& finishTimes,
                               Tensor<int>& finishPoints, std::vector<int>& unassigned,
                               std::unique_ptr<Types::CarData>& cars);
    void createSearchSpace(Tensor<int>& finishTimes, Tensor<int>& finishPoints,
                           std::vector<int>& unassigned, std::unique_ptr<Types::CarData>& cars);

    InputData& inputData;
    unsigned nTries, kBest;
	std::default_random_engine rng;

};

#endif // GENERATOR_H
