project(example)

add_executable(Example src/main.cpp)
target_link_libraries(Example OpenCLEvaluationGraph)
target_include_directories (Example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/../library/header)

find_package(OpenCL REQUIRED)
include_directories(${OPENCL_INCLUDE_DIRS})
target_link_libraries(Example ${OPENCL_LIBRARIES})