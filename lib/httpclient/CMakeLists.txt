add_library(httpclient STATIC client.h client.cpp)

target_link_libraries(httpclient PRIVATE cpr::cpr)

target_include_directories(httpclient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
