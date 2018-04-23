add_library(OutputData DataHandlers/OutputData.cpp)
target_include_directories(OutputData
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DataHandlers
        ${CMAKE_CURRENT_SOURCE_DIR}/Numeric
)

add_library(InputData DataHandlers/InputData.cpp)
target_include_directories(InputData
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DataHandlers
        ${CMAKE_CURRENT_SOURCE_DIR}/Numeric
)

add_library(Generator Algorithm/Generator.cpp)
target_include_directories(Generator
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Algorithm
		${CMAKE_CURRENT_SOURCE_DIR}/Numeric
)
target_link_libraries(Generator 
	PUBLIC
		InputData
)

add_executable(RideDistributor main.cpp)
target_link_libraries(RideDistributor PRIVATE OutputData InputData Generator)
