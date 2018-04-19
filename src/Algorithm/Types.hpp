#ifndef TYPES_H
#define TYPES_H

#include <memory>
#include <initializer_list>
#include "Tensor.hpp"

namespace Types {

	struct CarData {
        CarData(const unsigned size) :
            x({size}), y({size}), t({size}), p({size}) {};

        CarData(CarData& other):
            x(other.x), y(other.y), t(other.t), p(other.p) {};

		Tensor<int> x;
		Tensor<int> y;
		Tensor<int> t;
		Tensor<int> p;
	};

	struct Choice {
        Choice(CarData& other, const unsigned nUnassigned):
            cars(other), unassigned({nUnassigned}), score(0) {};

		CarData cars;
		Tensor<int> unassigned;
		float score;
	};

	using Choices = std::vector<std::unique_ptr<Choice>>;

}

#endif // TYPES_H
