add_library(OpenCLEvaluationGraphC SHARED src/ClGraphDefs.cpp header/c_cl_graph/ClGraphDefs.h)

target_link_libraries(OpenCLEvaluationGraphC OpenCLEvaluationGraph)
target_include_directories (OpenCLEvaluationGraphC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)

FILE(GLOB hdrs header/c_cl_graph/*.h)

set_target_properties(OpenCLEvaluationGraphC PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER ${hdrs})

add_definitions(-DOpenCLGraphCExport)

if(WIN32)
    install(TARGETS OpenCLEvaluationGraphC
            RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/c_cl_graph)
else()
    install(TARGETS OpenCLEvaluationGraphC
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/c_cl_graph)

endif()