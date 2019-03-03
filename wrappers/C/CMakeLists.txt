add_library(OpenCLEvaluationGraphC SHARED src/ClGraphDefs.cpp header/ClGraphDefs.h)

target_link_libraries(OpenCLEvaluationGraphC OpenCLEvaluationGraph)
target_include_directories (OpenCLEvaluationGraphC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)

add_definitions(-DOpenCLGraphCExport)
