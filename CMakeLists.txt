cmake_minimum_required(VERSION 3.10)

project(Oak VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_VERBOSE_MAKEFILE OFF)

add_executable(${PROJECT_NAME} "" )

find_package(SDL2 REQUIRED)
target_compile_options(${PROJECT_NAME} PRIVATE -pedantic -Wall -Werror)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
add_subdirectory("source")
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/chipset
        ${PROJECT_SOURCE_DIR}/include/chipset/arm2
        ${PROJECT_SOURCE_DIR}/include/chipset/arm2/opcodes
        ${PROJECT_SOURCE_DIR}/include/util
)

configure_file(${PROJECT_SOURCE_DIR}/include/Version.h.in ${PROJECT_SOURCE_DIR}/include/Version.h)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
)

add_subdirectory(test)
