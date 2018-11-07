include_directories(header)

add_library(OpenCLEvaluationGraph SHARED header/Node.h
        src/Node.cpp header/INode.h
        header/Data.h header/Device.h src/NodeAdd.cpp
        header/NodeAdd.h src/Device.cpp
        src/NodeData.cpp header/NodeData.h src/NodeMul.cpp header/NodeMul.h
        src/DataImpl.cpp header/DataImpl.h src/Data.cpp
		header/dll_macros.h
		header/CLHelper.h src/CLHelper.cpp)
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

add_definitions(-DDllExport)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/oxygen/doxygen.cmake)
ADD_DOCUMENTATION(doc Doxyfile)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/opencl/FindOpenCL.cmake)
find_package(OpenCL REQUIRED)
include_directories(${OPENCL_INCLUDE_DIRS})
target_link_libraries(OpenCLEvaluationGraph ${OPENCL_LIBRARIES})