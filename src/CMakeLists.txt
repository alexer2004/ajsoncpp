cmake_minimum_required(VERSION 2.8)

set(SOURCE_LIB array_getter.cpp jread.cpp jwrite.cpp jwrite_visitor.cpp map_getter.cpp null_object.cpp)

add_library(AJSON_OBJ OBJECT ${SOURCE_LIB})