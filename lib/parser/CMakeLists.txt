add_library(parser STATIC file_reader.h file_reader.cpp parser.h parser.cpp)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
