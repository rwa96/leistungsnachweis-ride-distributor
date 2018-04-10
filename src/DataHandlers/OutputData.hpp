#ifndef OUTPUTDATA_H

#include <memory>
#include <string>
#include <vector>
#include "Tensor.hpp"

class OutputData : public std::enable_shared_from_this<OutputData> {
public:

	OutputData(std::shared_ptr<OutputData> parent, std::unique_ptr<Tensor> value) 
		:parent(parent), value(std::move(value)) {};

	void writeToFile(const std::string path, const unsigned fleetSize) const;

private:

	std::shared_ptr<OutputData> parent;
	std::unique_ptr<Tensor> value;

	std::vector<std::vector<int>> createDataStructure(std::shared_ptr<const OutputData> start, const unsigned fleetSize) const;

};

#define OUTPUTDATA_H
#endif // OUTPUTDATA_H