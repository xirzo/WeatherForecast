add_library(file file_reader.h file_reader.cpp)

target_include_directories(file PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
