#ifndef TENSOR_T
#define TENSOR_T

template<typename T>
Tensor<T>::Tensor(const std::vector<unsigned> dims): dims(dims) {
    size = 1;

    for(auto& dim : dims) {
        size *= dim;
    }

    if(size == 0) {
        this->dims.clear();
    } else {
        data = std::shared_ptr<T[]>(new T[size]);
    }
}

template<typename T>
Tensor<T>::Tensor(const std::vector<unsigned> dims,
                  const std::vector<T> data): Tensor(dims) {
    for(unsigned i = 0; i < getSize(); ++i) {
        (*this)(i) = data[i];
    }
}

template<typename T>
Tensor<T>::Tensor(const std::vector<unsigned> dims, const T& defaultValue): Tensor(dims) {
    for(unsigned i = 0; i < getSize(); ++i) {
        (*this)(i) = defaultValue;
    }
}

template<typename T>
Tensor<T>::Tensor(const Tensor<T>& other): Tensor(other.getDims()) {
    for(unsigned i = 0; i < size; ++i) {
        (*this)(i) = other(i);
    }
}

template<typename T>
T& Tensor<T>::operator()(const int i) const
{return data[i];}

template<typename T>
T& Tensor<T>::operator()(const int row, const int col) const
{return data[row * dims[1] + col];}

template<typename T>
T& Tensor<T>::operator()(const int row, const int col, const int offset) const
{return data[row * dims[1] * dims[2] + col * dims[2] + offset];}

template<typename T>
Tensor<T>& Tensor<T>::operator=(const Tensor<T>& rhs) {
    size = rhs.size;
    dims = rhs.dims;
    data = rhs.data;
    return *this;
}

template<typename T>
const unsigned Tensor<T>::getSize() const
{return size;}

template<typename T>
const std::vector<unsigned> Tensor<T>::getDims() const
{return dims;}

#endif // TENSOR_T
