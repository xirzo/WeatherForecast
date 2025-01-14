add_library(weather STATIC weather_day.h weather_day.cpp forecast_factory.h
                           forecast_factory.cpp forecast.h forecast.cpp)

target_link_libraries(weather PRIVATE configuration)

target_include_directories(weather PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
