add_library(ui ui.h ui.cpp)

target_link_libraries(ui PRIVATE ftxui::screen ftxui::dom ftxui::component)
target_link_libraries(ui PRIVATE weather)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
