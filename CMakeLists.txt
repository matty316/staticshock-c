cmake_minimum_required(VERSION 3.29)

project(staticshock LANGUAGES C)

set(CMAKE_C_STANDARD 23)
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE MY_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

add_executable(staticshock "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

target_include_directories(staticshock PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries(staticshock mm_lib)
target_compile_options(staticshock PRIVATE -Wall -Wextra -g)
