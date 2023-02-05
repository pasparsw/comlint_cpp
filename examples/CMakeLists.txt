cmake_minimum_required(VERSION 3.10)

project(ComlintExamples)

set(PARSING_EXAMPLE_APP "parsing_example_app")
set(RUNNING_EXAMPLE_APP "running_example_app")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(COMLINT_CPP_DIR ${CMAKE_SOURCE_DIR}/comlint_cpp)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

add_executable(${PARSING_EXAMPLE_APP})
add_executable(${RUNNING_EXAMPLE_APP})

target_include_directories(${PARSING_EXAMPLE_APP} PRIVATE
    ${COMLINT_CPP_DIR}/include
)
target_include_directories(${RUNNING_EXAMPLE_APP} PRIVATE
    ${COMLINT_CPP_DIR}/include
)

target_sources(${PARSING_EXAMPLE_APP} PRIVATE
    ${CMAKE_SOURCE_DIR}/parsing_example_main.cpp
)
target_sources(${RUNNING_EXAMPLE_APP} PRIVATE
    ${CMAKE_SOURCE_DIR}/running_example_main.cpp
)

find_library(COMLINT_CPP_LIB NAMES ComlintCpp HINTS ${COMLINT_CPP_DIR})

target_link_libraries(${PARSING_EXAMPLE_APP} PRIVATE
    ${COMLINT_CPP_LIB}
)
target_link_libraries(${RUNNING_EXAMPLE_APP} PRIVATE
    ${COMLINT_CPP_LIB}
)

if (UNIX)
    install(TARGETS ${PARSING_EXAMPLE_APP} DESTINATION ${CMAKE_BINARY_DIR}/bin)
    install(TARGETS ${RUNNING_EXAMPLE_APP} DESTINATION ${CMAKE_BINARY_DIR}/bin)
    install(FILES ${COMLINT_CPP_DIR}/libComlintCpp.so DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif(UNIX)

if (WIN32)
    install(FILES ${COMLINT_CPP_DIR}/ComlintCpp.dll DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
endif(WIN32)