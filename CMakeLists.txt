cmake_minimum_required(VERSION 3.10)
project(snake CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory(src CLIST)
include_directories(include)
add_executable(main ${CLIST})
target_link_libraries(main ncurses)
