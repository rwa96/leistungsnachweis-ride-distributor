add_executable(TensorTest Numeric/TensorTest.cpp)
target_link_libraries(TensorTest PRIVATE gtest gmock Tensor)
add_test(NAME TensorTest COMMAND TensorTest)
