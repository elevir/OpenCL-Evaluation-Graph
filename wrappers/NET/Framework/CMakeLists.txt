cmake_minimum_required(VERSION 3.12.4)

add_library(OpenCLEvaluationGraphManaged SHARED
    src/ManagedData.h src/ManagedData.cpp
    src/ManagedDevice.h src/ManagedDevice.cpp
    src/ManagedNode.h src/ManagedNode.cpp
	src/Utilities.hpp)

set_target_properties(OpenCLEvaluationGraphManaged PROPERTIES COMMON_LANGUAGE_RUNTIME "")

target_link_libraries(OpenCLEvaluationGraphManaged OpenCLEvaluationGraph)
target_include_directories (OpenCLEvaluationGraphManaged PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)