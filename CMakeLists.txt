cmake_minimum_required(VERSION 3.7)
project(safe_string)

include_directories(
    include
)

add_library( ${PROJECT_NAME}_LIB
    src/safe_string.c
)

add_executable(${PROJECT_NAME} safe_test.c)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_LIB)