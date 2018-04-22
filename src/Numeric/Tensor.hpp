#ifndef TENSOR_H
#define TENSOR_H

#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <algorithm>

#define MAX_SHOWN_ENTRIES (unsigned)20


template<typename T>
class Tensor {
public:

    /** Creates an empty Tensor. */
    Tensor(): size(0) {};

    /**
     * Creates a n-dimensional Tensor.
     *
     * \param [in] dims list that defines the dimensions of this Tensor
     */
    Tensor(const std::vector<unsigned> dims): dims(dims) {
        size = 1;

        for(auto& dim : dims) {
            size *= dim;
        }

        if(size == 0) {
            this->dims.clear();
        } else {
            data = std::make_unique<T[]>(size);
        }
    };

    /**
     * Creates a tensor from an existing array.
     *
     * \param [in] dims list that defines the dimensions of this Tensor
     * \param [in] data pointer to existing array
     */
    Tensor(const std::vector<unsigned> dims, const std::vector<T> data): Tensor(dims) {
        for(unsigned i = 0; i < getSize(); ++i) {
            (*this)(i) = data[i];
        }
    };

    /**
     * Creates a deep copy of a given Tensor.
     *
     * \param [in] other Tensor to copy
     */
    Tensor(Tensor<T>& other): Tensor(other.getDims()) {
        for(unsigned i = 0; i < size; ++i) {
            (*this)(i) = other(i);
        }
    };

    /**
     * Returns a string representation of the stored data.
     * \note this should only be used for debug purposes
     *
     * \return std::string String represenation of internal data
     */
    std::string str() const {
        std::ostringstream result;

        result << '[';

        for(unsigned i = 0; i < std::min(size, MAX_SHOWN_ENTRIES); ++i) {
            result << data[i];

            if(i < size - 1) {result << ", ";}
            else if(size > MAX_SHOWN_ENTRIES) {result << "...";}
        }

        result << ']' << std::endl;

        return result.str();
    };

    /**
     * One dimensional array access (list index)
     *
     * \param [in] i
     * \return T& data at given index
     */
    inline T& operator()(const int i)
    {return data[i];};

    /**
     * Two dimensional array access (matrix)
     *
     * \param [in] row
     * \param [in] col
     * \return T& data at given position
     */
    inline T& operator()(const int row, const int col)
    {return data[row * dims[1] + col];};

    /**
     * Three dimensional array access (3D matrix)
     *
     * \param [in] row
     * \param [in] col
     * \param [in] offset
     * \return T& data at given position
     */
    inline T& operator()(const int row, const int col, const int offset)
    {return data[row * dims[1] * dims[2] + col * dims[2] + offset];};

    /**
     * Total number of elements that can be stored in this tensor.
     *
     * \return unsigned size of the internal data structure.
     */
    inline const unsigned getSize() const
    {return size;};

    /**
     * List of dimension of this Tensor.
     *
     * \return std::vector<unsigned> list of dimensions
     */
    const std::vector<unsigned> getDims() const
    {return dims;};

private:

    /** Size of internal data structure. */
    unsigned size;

    /** Dimensions defined at initialization. */
    std::vector<unsigned> dims;

    /** Internal data structure. */
    std::unique_ptr<T[]> data;

};

#endif // TENSOR_H
