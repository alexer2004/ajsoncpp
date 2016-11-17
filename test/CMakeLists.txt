cmake_minimum_required (VERSION 2.8)

project (json)

add_executable (${PROJECT_NAME} json.cpp)

target_link_libraries (${PROJECT_NAME} jsoncpp)

add_dependencies (${PROJECT_NAME} jsoncpp)