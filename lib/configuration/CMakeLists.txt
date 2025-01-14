add_library(configuration STATIC configuration.h configuration.cpp)

target_link_libraries(configuration PRIVATE parser)

target_include_directories(configuration PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
