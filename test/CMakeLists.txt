find_package(GTest REQUIRED)

add_library(InputDataTest DataHandlers/InputDataTest.cpp)
target_include_directories(InputDataTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/DataHandlers)
target_link_libraries(InputDataTest PRIVATE InputData GTest::GTest)

add_library(OutputDataTest DataHandlers/OutputDataTest.cpp)
target_include_directories(OutputDataTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/DataHandlers)
target_link_libraries(OutputDataTest PRIVATE OutputData GTest::GTest)

add_executable(UnitTests test.cpp)
target_link_libraries(UnitTests PRIVATE InputDataTest OutputDataTest GTest::Main)
add_test(NAME AllUnitTests COMMAND UnitTests)
