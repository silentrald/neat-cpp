cmake_minimum_required(VERSION 3.13.4)

project(main)

add_executable(${PROJECT_NAME} test/xor.cpp)

add_subdirectory(src)
target_link_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} neat)
