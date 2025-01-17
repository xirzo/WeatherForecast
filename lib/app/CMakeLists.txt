add_library(application app.h app.cpp)

target_link_libraries(application PUBLIC file)
target_link_libraries(application PUBLIC httpclient)
target_link_libraries(application PUBLIC configuration)
target_link_libraries(application PUBLIC weather)
target_link_libraries(application PUBLIC ui)
target_link_libraries(application PUBLIC ftxui::screen ftxui::dom
                                         ftxui::component)
target_link_libraries(application PUBLIC json_parser::jsonparser)

target_include_directories(application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
