project(ExampleJava VERSION 1.0.0 LANGUAGES Java)

set(JAVA_SOURCE_DIRECTORY java)
add_jar(ExampleJava com/example/Main.java
        ENTRY_POINT com/example/Main
        MANIFEST "${CMAKE_CURRENT_SOURCE_DIR}/MANIFEST.MF"
        INCLUDE_JARS OpenCLEvaluationGraphJavaAPI)