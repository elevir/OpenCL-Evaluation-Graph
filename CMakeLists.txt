cmake_minimum_required(VERSION 3.9)
project(OpenCL_Evaluation_Graph VERSION 0.0.1 DESCRIPTION "OpenCL evaluation graph library")

include(GNUInstallDirs)

add_library(OpenCLEvaluationGraph SHARED src/NodeImpl.cpp header/Node.h src/Node.cpp src/NodeImpl.h)
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

set(CMAKE_CXX_STANDARD 14)