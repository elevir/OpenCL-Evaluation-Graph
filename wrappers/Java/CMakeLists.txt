cmake_minimum_required(VERSION 3.12.4)

set(JAVA_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_jar(OpenCLEvaluationGraphJavaAPI
        ${CMAKE_CURRENT_SOURCE_DIR}/com/clgraph/Data.java
       # ${CMAKE_CURRENT_SOURCE_DIR}/com/clgraph/Device.java
        GENERATE_NATIVE_HEADERS OpenCLEvaluationGraphJavaHeaders)

add_library(OpenCLEvaluationGraphJava SHARED src/JData.cpp)

target_link_libraries(OpenCLEvaluationGraphJava OpenCLEvaluationGraphC)
target_link_libraries(OpenCLEvaluationGraphJava OpenCLEvaluationGraphJavaHeaders)

include_directories(${JNI_INCLUDE_DIRS})
target_link_libraries(OpenCLEvaluationGraphJava ${JNI_LIBRARIES})