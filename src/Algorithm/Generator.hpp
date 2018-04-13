#ifndef GENERATOR_H
#define GENERATOR_H

#include "Types.hpp"
#include "Tensor.hpp"
#include "InputData.hpp"

class Generator {
public:

	Generator(unsigned expandSize, unsigned nTries, unsigned kBest) :
		expandSize(expandSize), nTries(nTries), kBest(kBest) {};

	Types::Choices generate(InputData& inputData, std::unique_ptr<Tensor<int>> unassigned, std::unique_ptr<Types::CarData> cars);

private:

	unsigned expandSize, nTries, kBest;

}

#endif // GENERATOR_H