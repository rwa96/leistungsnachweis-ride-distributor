#ifndef TENSOR_H
#define TENSOR_H

#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <algorithm>

#ifndef NDEBUG
#include <iostream>

#define DBG_PRINT_2D_TENSOR(s, m) std::cout << s << std::endl; \
    for(unsigned r = 0; r < m.getDims()[0]; ++r){ \
        for(unsigned c = 0; c < m.getDims()[1]; ++c){ \
            std::cout << m(r, c); \
            if(c < m.getDims()[1] - 1) std::cout << ", "; \
        } \
        std::cout << std::endl; \
    }

#define DBG_PRINT_1D_TENSOR(s, v) std::cout << s << std::endl; \
    for(unsigned i = 0; i < v.getDims()[0]; ++i){ \
        std::cout << v(i); \
        if(i < v.getDims()[0] - 1) std::cout << ", "; \
    } \
    std::cout << std::endl
#else
#define DBG_PRINT_2D_TENSOR(_, _)
#define DBG_PRINT_1D_TENSOR(_, _)
#endif

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
    Tensor(const std::vector<unsigned> dims);

    /**
     * Creates a tensor from an existing array.
     *
     * \param [in] dims list that defines the dimensions of this Tensor
     * \param [in] data pointer to existing array
     */
    Tensor(const std::vector<unsigned> dims, const std::vector<T> data);

    /**
    * Creates a n-dimensional Tensor and sets entries to a default Value.
    *
    * \param [in] dims list that defines the dimensions of this Tensor
    * \param [in] defaultValue default value for all entries
    */
    Tensor(const std::vector<unsigned> dims, const T& defaultValue);

    /**
     * Creates a deep copy of a given Tensor.
     *
     * \param [in] other Tensor to copy
     */
    Tensor(const Tensor<T>& other);

    /**
     * One dimensional array access (list index)
     *
     * \param [in] i
     * \return T& data at given index
     */
    inline T& operator()(const int i) const;

    /**
     * Two dimensional array access (matrix)
     *
     * \param [in] row
     * \param [in] col
     * \return T& data at given position
     */
    inline T& operator()(const int row, const int col) const;

    /**
     * Three dimensional array access (3D matrix)
     *
     * \param [in] row
     * \param [in] col
     * \param [in] offset
     * \return T& data at given position
     */
    inline T& operator()(const int row, const int col, const int offset) const;

    /**
     * This operator does NOT copy data but points to the assigned object's data.
     *
     * \note Tensor does not check integrity of internal data which could lead logic
     *       errors when multiple instances point to the same data
     *
     * \param rhs object used to assign to this instance
     * \return Tensor<T>& this instance
     */
    Tensor<T>& operator=(const Tensor<T>& rhs);

    /**
     * Total number of elements that can be stored in this tensor.
     *
     * \return unsigned size of the internal data structure.
     */
    const unsigned getSize() const;

    /**
     * List of dimension of this Tensor.
     *
     * \return std::vector<unsigned> list of dimensions
     */
    const std::vector<unsigned> getDims() const;

private:

    /** Size of internal data structure. */
    unsigned size;

    /** Dimensions defined at initialization. */
    std::vector<unsigned> dims;

    /** Internal data structure. */
    std::shared_ptr<T[]> data;

};

#include "Tensor.tpp"

#endif // TENSOR_H
