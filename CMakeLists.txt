cmake_minimum_required(VERSION 2.8)

project(ajsoncpp)

include_directories(include)

add_subdirectory(src)

add_library(${PROJECT_NAME} STATIC $<TARGET_OBJECTS:AJSON_OBJ>)

target_link_libraries(${PROJECT_NAME})

add_subdirectory(test)