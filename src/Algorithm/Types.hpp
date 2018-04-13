#ifndef TYPES_H
#define TYPES_H

#include <memory>
#include "Tensor.hpp"

namespace Types {

	struct CarData {
		Tensor<int> x;
		Tensor<int> y;
		Tensor<int> t;
		Tensor<int> p;
	};

	struct Choice {
		CarData cars;
		Tensor<int> unassigned;
		float score;
	};

	using Choices = std::vector<std::unique_ptr<Choice>>;

}

#endif // TYPES_H
