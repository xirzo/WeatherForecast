cmake_minimum_required(VERSION 3.12)

add_library(requests STATIC request.h request.cpp)

find_package(cpr REQUIRED)

target_link_libraries(requests PRIVATE cpr::cpr)

target_include_directories(requests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
