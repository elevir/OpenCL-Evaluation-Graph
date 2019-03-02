cmake_minimum_required(VERSION 3.12.4)
project(OpenCL_Evaluation_Graph VERSION 0.0.1 DESCRIPTION "OpenCL evaluation graph library")

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

add_subdirectory(library)
add_subdirectory(tests)
add_subdirectory(example/cplusplus)

if (WIN32)
set(WIN32_PROJECTS OpenCLEvaluationGraphManaged ExampleDotNet)
add_subdirectory(wrappers/NET/Framework)
add_subdirectory(example/dotnet)
else()
set(WIN32_PROJECTS)
endif()

set_target_properties(OpenCLEvaluationGraph Tests Example ${WIN32_PROJECTS}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
