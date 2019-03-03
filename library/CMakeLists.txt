include_directories(header)

add_library(OpenCLEvaluationGraph SHARED
        header/cl_graph/Definitions.h
        header/cl_graph/Data.h
        header/cl_graph/Device.h
        header/cl_graph/Node.h
        src/Data.cpp
        src/DataImpl.h
        src/DataImpl.cpp
        src/Device.cpp
        src/DeviceImpl.h
        src/DeviceImpl.cpp
        src/INode.h
        src/helpers/opencl.h
        src/Node.cpp
        src/NodeAdd.h
        src/NodeAdd.cpp
        src/NodeData.h
        src/NodeData.cpp
        src/NodeMul.h
        src/NodeMul.cpp
        src/helpers/CLTypeConverters.h
        src/helpers/ClKernelsDefinitions.h
        src/NodeMulElemWise.cpp
        src/NodeMulElemWise.h 
        src/NodeAbs.cpp 
        src/NodeAbs.h
        src/NodeSqrt.cpp 
        src/NodeSqrt.h
        header/cl_graph/Data.inl
        src/NodeDivElemWise.cpp 
        src/NodeDivElemWise.h
        src/NodeUnaryMinus.cpp 
        src/NodeUnaryMinus.h
        src/NodeUnaryOp.cpp 
        src/NodeUnaryOp.h
        src/NodeTwoOp.cpp
        src/NodeTwoOp.h)

FILE(GLOB hdrs header/cl_graph/*.h)

set_target_properties(OpenCLEvaluationGraph PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER "${hdrs}")

target_include_directories(OpenCLEvaluationGraph PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)

if(WIN32)
    install(TARGETS OpenCLEvaluationGraph
            RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cl_graph)
else()
    install(TARGETS OpenCLEvaluationGraph
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cl_graph)

endif()

if (APPLE)
    ADD_DEFINITIONS(-DCL_SILENCE_DEPRECATION)
    ADD_DEFINITIONS(-D__APPLE_CL__)
endif()

add_definitions(-DOpenCLGraphExport)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/oxygen/doxygen.cmake)
ADD_DOCUMENTATION(doc Doxyfile)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
target_link_libraries(OpenCLEvaluationGraph ${OpenCL_LIBRARIES})