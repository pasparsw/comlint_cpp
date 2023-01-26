cmake_minimum_required(VERSION 3.10)

project(ComlintCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_DIRS ${CMAKE_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} SHARED)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIRS}
)

target_sources(${PROJECT_NAME} PRIVATE
    ${SOURCE_DIRS}/command_line_interface.cpp
    ${SOURCE_DIRS}/interface_validator.cpp
)

enable_testing()

add_subdirectory(libs/googletest)
add_subdirectory(test)