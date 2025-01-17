add_library(configuration city.h city.cpp configuration.h configuration.cpp
                          configuration_factory.h configuration_factory.cpp)

target_link_libraries(configuration PRIVATE file)
target_link_libraries(configuration PRIVATE httpclient)
target_link_libraries(configuration PRIVATE json_parser::jsonparser)

target_include_directories(configuration PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
