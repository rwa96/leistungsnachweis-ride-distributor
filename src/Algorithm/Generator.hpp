#ifndef GENERATOR_H
#define GENERATOR_H

#include "Types.hpp"
#include "Tensor.hpp"
#include "InputData.hpp"
#include "SearchGraphNode.hpp"

class Generator {
public:

    Generator(InputData& inputData):inputData(inputData){};

    void generate(Types::Choices& output, std::shared_ptr<SearchGraphNode>& prevNode,
                  std::vector<int>& unassigned,
                  std::unique_ptr<Types::CarData> cars);

private:

    void selectFromSearchSpace(Types::Choices& output,
                               std::shared_ptr<SearchGraphNode>& prevNode, Tensor<int>& finishTimes,
                               Tensor<int>& finishPoints, std::vector<int>& unassigned,
                               int maxValue, std::unique_ptr<Types::CarData>& cars);
    int createSearchSpace(Tensor<int>& finishTimes, Tensor<int>& finishPoints,
                           std::vector<int>& unassigned, std::unique_ptr<Types::CarData>& cars);

    InputData& inputData;

};

#endif // GENERATOR_H
