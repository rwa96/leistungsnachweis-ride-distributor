# libraries
add_subdirectory (DataHandlers)
set (EXTRA_LIBS ${EXTRA_LIBS} InputData OutputData)

# add the executable
add_executable (RideDistributor main.cpp)
target_link_libraries (RideDistributor ${EXTRA_LIBS})
