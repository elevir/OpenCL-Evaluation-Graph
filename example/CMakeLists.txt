project(example)

add_executable(Example src/main.cpp)
target_link_libraries(Example OpenCLEvaluationGraph)
target_include_directories (Example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/)