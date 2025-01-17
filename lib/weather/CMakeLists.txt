add_library(
  weather
  forecast.h
  forecast.cpp
  forecast_factory.h
  forecast_factory.cpp
  weather_day.h
  weather_day.cpp
  weather_parser.h
  weather_parser.cpp
  weather_period.h
  weather_period.cpp)

target_link_libraries(weather PRIVATE configuration)
target_link_libraries(weather PRIVATE httpclient)
target_link_libraries(weather PRIVATE json_parser::jsonparser)

target_include_directories(weather PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
