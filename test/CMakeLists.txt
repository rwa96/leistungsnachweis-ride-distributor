include(gtest.cmake)

add_library(InputDataTest DataHandlers/InputDataTest.cpp)
target_include_directories(InputDataTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/DataHandlers)
target_link_libraries(InputDataTest PRIVATE InputData libgtest)

add_library(OutputDataTest DataHandlers/OutputDataTest.cpp)
target_include_directories(OutputDataTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/DataHandlers)
target_link_libraries(OutputDataTest PRIVATE OutputData libgtest)

add_library(UtilsTest Utils/UtilsTest.cpp)
target_include_directories(UtilsTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Utils)

add_executable(UnitTests test.cpp)
target_link_libraries(UnitTests
    PRIVATE
        InputDataTest
        OutputDataTest
        UtilsTest
        libgtest
)
add_test(NAME AllUnitTests COMMAND UnitTests)
