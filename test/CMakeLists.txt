add_executable(TensorTest Numeric/TensorTest.cpp)
target_link_libraries(TensorTest PRIVATE gtest gmock Tensor --coverage)
target_compile_options(TensorTest PRIVATE --coverage)
add_test(NAME TensorTest COMMAND TensorTest)
