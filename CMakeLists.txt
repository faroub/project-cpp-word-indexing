cmake_minimum_required(VERSION 3.2)

project(WordIndexing)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME})
add_subdirectory(src)
add_executable(${PROJECT_NAME} "app/main.cpp")
target_link_libraries(${PROJECT_NAME} WordIndexingLib -lpthread)
