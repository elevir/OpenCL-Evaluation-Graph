cmake_minimum_required(VERSION 3.12.4)
project(OpenCL_Evaluation_Graph VERSION 0.0.1 DESCRIPTION "OpenCL evaluation graph library")

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

add_subdirectory(library)
add_subdirectory(tests)
add_subdirectory(example/cplusplus)
add_subdirectory(wrappers/C)

set(OPTIONAL_PROJECTS)
if (WIN32)
set(OPTIONAL_PROJECTS ${OPTIONAL_PROJECTS} OpenCLEvaluationGraphManaged ExampleDotNet)
add_subdirectory(wrappers/NET/Framework)
add_subdirectory(example/dotnet)
endif()

find_package(Java)
find_package(JNI)
if (JNI_FOUND)
    if (Java_FOUND)
        include(UseJava)
        add_subdirectory(wrappers/Java)
        add_subdirectory(example/Java)
        set(OPTIONAL_PROJECTS ${OPTIONAL_PROJECTS} OpenCLEvaluationGraphJava ExampleJava)
    endif()
endif()

set_target_properties(OpenCLEvaluationGraph Tests Example ${OPTIONAL_PROJECTS}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
