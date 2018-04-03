find_package(Boost REQUIRED)

add_library(OutputData DataHandlers/OutputData.cpp)
target_include_directories(OutputData
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DataHandlers
		${Boost_INCLUDE_DIRS}
)

add_library(InputData DataHandlers/InputData.cpp)
target_include_directories(InputData
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DataHandlers
		${Boost_INCLUDE_DIRS}
)

add_executable(RideDistributor main.cpp)
target_link_libraries(RideDistributor PRIVATE OutputData InputData)
