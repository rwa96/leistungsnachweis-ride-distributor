#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H

#include <memory>
#include <string>
#include <vector>
#include <list>
#include "Tensor.hpp"

/**
 * Node of the search tree that is created when exploring various car-ride distributions.
 * Each node can traverse its parent tree and create an output file.
 */
class OutputData {
public:

    /**
     * Creates a new root node (no parent) containing a value.
     *
     * \param [in,out] value Tensor value of this node
     */
    OutputData(std::unique_ptr<Tensor<unsigned>>& value): value(std::move(value)) {};

    /**
     * Creates a new node associated with a parent tree and containing a value.
     *
     * \param [in,out] parent parent node
     * \param [in,out] value Tensor value of this node
     */
    OutputData(std::shared_ptr<OutputData>& parent, std::unique_ptr<Tensor<unsigned>>& value)
        : parent(parent), value(std::move(value)) {};

    /**
     * Writes the value of this node and of all its parents to a specified file.
     *
     * \param [in] path specified file
     * \param [in] fleetSize number of lines the file will contain
     * \throw std::fstream::failure if file couldn't be opened/created
     */
    void writeToFile(const std::string path, const unsigned fleetSize) const;

private:

    /** Parent node. */
    std::shared_ptr<OutputData> parent;

    /** Value of this node. */
    std::unique_ptr<Tensor<unsigned>> value;

    /**
     * Creates a 2D vector of values while traversing parent nodes.
     *
     * \param [in] start first node for traversal
     * \param [in] fleetSize number of vectors in 2D-vector
     * \return std::vector<std::list<int>> each list represents a car and its rides
     */
    std::vector<std::list<unsigned>> createDataStructure(const unsigned fleetSize) const;

};

#endif // OUTPUTDATA_H
