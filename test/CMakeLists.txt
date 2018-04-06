include(gtest.cmake)

add_library(TensorTest Numeric/TensorTest.cpp)
target_link_libraries(TensorTest
    PRIVATE
        libgtest
        Tensor
)

add_executable(UnitTests test.cpp)
target_link_libraries(UnitTests
    PRIVATE
        libgtest
        TensorTest
)

add_test(NAME AllUnitTests COMMAND UnitTests)
