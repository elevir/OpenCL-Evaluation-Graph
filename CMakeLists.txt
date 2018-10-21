cmake_minimum_required(VERSION 3.9)
project(OpenCL_Evaluation_Graph VERSION 0.0.1 DESCRIPTION "OpenCL evaluation graph library")

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

include_directories(header)

add_library(OpenCLEvaluationGraph SHARED header/Node.h
        src/Node.cpp src/INode.h
        header/Data.h header/Device.h src/NodeAdd.cpp
        src/NodeAdd.h src/Device.cpp
        src/NodeData.cpp src/NodeData.h src/NodeMul.cpp src/NodeMul.h
        src/DataImpl.cpp src/DataImpl.h src/Data.cpp)
set_target_properties(OpenCLEvaluationGraph PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER header/Node.h)

target_include_directories(OpenCLEvaluationGraph PRIVATE .)

if(WIN32)
    install(TARGETS OpenCLEvaluationGraph
            RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
else()
    install(TARGETS OpenCLEvaluationGraph
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

endif()