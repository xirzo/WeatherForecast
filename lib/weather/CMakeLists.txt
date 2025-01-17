add_library(weather weather_day.h weather_day.cpp forecast_factory.h
                    forecast_factory.cpp forecast.h forecast.cpp)

target_link_libraries(weather PRIVATE configuration)
target_link_libraries(weather PRIVATE httpclient)
target_link_libraries(weather PRIVATE file)
target_link_libraries(weather PRIVATE json_parser::jsonparser)

target_include_directories(weather PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
