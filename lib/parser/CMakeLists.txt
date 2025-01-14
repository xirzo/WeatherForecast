add_library(
  parser STATIC
  converter.h
  converter.cpp
  file_reader.h
  file_reader.cpp
  json_value.h
  parser.h
  parser.cpp)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
