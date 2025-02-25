cmake_minimum_required(VERSION 3.12)

project(
  weather_forecast
  VERSION 0.1
  LANGUAGES CXX
  DESCRIPTION "Weather forecast app")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake/json_parser")
set(json_parser_DIR "/usr/local/lib/cmake/json_parser")

find_package(cpr REQUIRED)
find_package(ftxui 5 REQUIRED)
find_package(json_parser 1.0 REQUIRED)

add_subdirectory(lib)
add_subdirectory(bin)
