add_executable(TensorTest Numeric/TensorTest.cpp)
target_link_libraries(TensorTest PRIVATE gtest gmock)
target_include_directories(TensorTest PRIVATE ${PROJECT_SOURCE_DIR}/src/Numeric)
add_test(NAME TensorTest COMMAND TensorTest)

add_executable(InputDataTest DataHandlers/InputDataTest.cpp)
target_include_directories(InputDataTest PRIVATE DataHandlers)
target_link_libraries(InputDataTest PRIVATE gtest gmock InputData)
add_test(NAME InputDataTest COMMAND InputDataTest)

add_executable(OutputDataTest DataHandlers/OutputDataTest.cpp)
target_include_directories(OutputDataTest PRIVATE DataHandlers)
target_link_libraries(OutputDataTest PRIVATE gtest gmock OutputData)
add_test(NAME OutputDataTest COMMAND OutputDataTest)

add_executable(GeneratorTest Algorithm/GeneratorTest.cpp)
target_include_directories(GeneratorTest PRIVATE Algorithm)
target_link_libraries(GeneratorTest PRIVATE gtest gmock Generator)
#add_test(NAME GeneratorTest COMMAND GeneratorTest)
