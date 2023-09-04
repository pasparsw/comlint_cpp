cmake_minimum_required(VERSION 3.10)

project(ComlintCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/comlint)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INSTALLATION_DIR ${CMAKE_BINARY_DIR}/comlint_cpp)
set(EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)

add_definitions(-DEXPORT_COMLINT_API=1)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

add_library(${PROJECT_NAME} SHARED)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIR}
)

target_sources(${PROJECT_NAME} PRIVATE
    ${SOURCE_DIR}/command_line_interface.cpp
    ${SOURCE_DIR}/interface_helper.cpp
    ${SOURCE_DIR}/interface_validator.cpp
    ${SOURCE_DIR}/parsed_command.cpp
    ${SOURCE_DIR}/utils.cpp
)

if (BUILD_UNIT_TESTS)
    enable_testing()

    add_subdirectory(libs/googletest)
    add_subdirectory(test)
endif()

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
    BASE_NAME ${PROJECT_NAME}
    EXPORT_MACRO_NAME PUBLIC_COMLINT_API
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/comlint/export_comlint_api.hpp
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALLATION_DIR})
install(DIRECTORY ${INCLUDE_DIR}/ DESTINATION ${INSTALLATION_DIR}/include/comlint FILES_MATCHING PATTERN "*.hpp")
install(DIRECTORY ${INSTALLATION_DIR} DESTINATION ${EXAMPLES_DIR})