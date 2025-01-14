add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE requests)
target_link_libraries(${PROJECT_NAME} PRIVATE parser)
target_link_libraries(${PROJECT_NAME} PRIVATE configuration)
