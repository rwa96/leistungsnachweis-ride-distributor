#ifndef GENERATOR_H
#define GENERATOR_H

#include "Types.hpp"
#include "Tensor.hpp"
#include "InputData.hpp"

class Generator {
public:

	Generator(InputData& inputData, unsigned expandSize, unsigned nTries, unsigned kBest) :
		inputData(inputData), expandSize(expandSize), nTries(nTries), kBest(kBest) {};

	Types::Choices generate(std::unique_ptr<Tensor<int>> unassigned, std::unique_ptr<Types::CarData> cars);

private:

    InputData& inputData;
	unsigned expandSize, nTries, kBest;

};

#endif // GENERATOR_H
