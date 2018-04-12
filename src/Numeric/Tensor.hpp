#ifndef TENSOR_H
#define TENSOR_H

#include <string>
#include <memory>
#include <initializer_list>
#include <vector>
#include <sstream>
#include <algorithm>

#define MAX_SHOWN_ENTRIES (unsigned)20


template<typename T>
class Tensor{
public:

	/** Creates an empty Tensor. */
    Tensor():size(0){};

    /**
     * Creates a n-dimensional Tensor.
     *
     * \param [in] args list that defines the dimensions of this Tensor
     */
    Tensor(std::initializer_list<unsigned> args):dims(args){
        size = 1;
        for(auto& dim: dims){
            size *= dim;
        }
        if(size == 0){
            dims.clear();
        }
        data = std::make_unique<T[]>(size);
    };

    /**
     * Returns a string representation of the stored data.
     * \note this should only be used for debug purposes
     *
     * \return std::string String represenation of internal data
     */
    std::string str() const{
        std::ostringstream result;

        result << '[';
        for(unsigned i = 0; i < std::min(size, MAX_SHOWN_ENTRIES); ++i){
            result << data[i];
            if(i < size-1){result << ", ";}
            else if(size > MAX_SHOWN_ENTRIES){result << "...";}
        }
        result << ']' << std::endl;

        return result.str();
    };

    /**
	 * One dimensional array access (list index)
	 *
	 * \param [in] x
	 * \return T& data at given index
	 */
    inline T& operator()(const int x)
    {return data[x];};

    /**
     * Two dimensional array access (matrix)
     *
     * \param [in] x
     * \param [in] y
     * \return T& data at given position
     */
    inline T& operator()(const int x, const int y)
    {return data[x*dims[1] + y];};

    /**
     * Three dimensional array access (3D matrix)
     *
     * \param [in] x
     * \param [in] y
     * \param [in] z
     * \return T& data at given position
     */
    inline T& operator()(const int x, const int y, const int z)
    {return data[x*dims[1]*dims[2] + y*dims[2] + z];};

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
