add_library(Tensor Numeric/Tensor.cpp)
target_include_directories(Tensor
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Numeric
)

add_library(OutputData DataHandlers/OutputData.cpp)
target_include_directories(OutputData
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DataHandlers
)
target_link_libraries(OutputData
	PUBLIC
		Tensor
)

add_library(InputData DataHandlers/InputData.cpp)
target_include_directories(InputData
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DataHandlers
)
target_link_libraries(InputData
    PUBLIC
        Tensor
)

add_executable(RideDistributor main.cpp)
target_link_libraries(RideDistributor PRIVATE OutputData InputData Tensor)
