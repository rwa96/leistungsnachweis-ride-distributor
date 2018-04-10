add_executable(TensorTest Numeric/TensorTest.cpp)
target_link_libraries(TensorTest PRIVATE gtest gmock Tensor)
add_test(NAME TensorTest COMMAND TensorTest)

add_executable(InputDataTest DataHandlers/InputDataTest.cpp)
target_include_directories(InputDataTest PRIVATE DataHandlers)
target_link_libraries(InputDataTest PRIVATE gtest gmock InputData)
add_test(NAME InputDataTest COMMAND InputDataTest)
