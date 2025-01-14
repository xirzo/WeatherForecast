add_library(application STATIC app.h app.cpp)

target_link_libraries(application PUBLIC httpclient)
target_link_libraries(application PUBLIC parser)
target_link_libraries(application PUBLIC configuration)
target_link_libraries(application PUBLIC ftxui::screen ftxui::dom
                                         ftxui::component)

target_include_directories(application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
