cmake_minimum_required(VERSION 3.10)

project(ExampleApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(COMLINT_CPP_LIB_DIR ${CMAKE_SOURCE_DIR}/../build/Debug)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

find_library(COMLINT_CPP_LIB NAMES ComlintCpp HINTS ${COMLINT_CPP_LIB_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${COMLINT_CPP_LIB}
)

install(DIRECTORY ${COMLINT_CPP_LIB_DIR}/ DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE} FILES_MATCHING PATTERN "ComlintCpp.dll")