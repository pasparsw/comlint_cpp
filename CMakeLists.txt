cmake_minimum_required(VERSION 3.10)

project(ComlintCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
SET(CMAKE_INSTALL_PREFIX ".")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

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

enable_testing()

add_subdirectory(example)
add_subdirectory(libs/googletest)
add_subdirectory(test)

set(PUBLIC_HEADERS
    ${INCLUDE_DIR}/command_line_element_type.hpp
    ${INCLUDE_DIR}/command_line_interface.hpp
    ${INCLUDE_DIR}/command_properties.hpp
    ${INCLUDE_DIR}/flag_properties.hpp
    ${INCLUDE_DIR}/interface_helper.hpp
    ${INCLUDE_DIR}/interface_validator.hpp
    ${INCLUDE_DIR}/option_properties.hpp
    ${INCLUDE_DIR}/parsed_command.hpp
    ${INCLUDE_DIR}/types.hpp
    ${INCLUDE_DIR}/utils.hpp
    ${INCLUDE_DIR}/comlint_exception.hpp
    ${INCLUDE_DIR}/forbidden_flag.hpp
    ${INCLUDE_DIR}/forbidden_option_value.hpp
    ${INCLUDE_DIR}/forbidden_option.hpp
    ${INCLUDE_DIR}/invalid_command_position.hpp
    ${INCLUDE_DIR}/missing_command_value.hpp
    ${INCLUDE_DIR}/missing_option_value.hpp
    ${INCLUDE_DIR}/unsupported_command_value.hpp
    ${INCLUDE_DIR}/unsupported_command.hpp
    ${INCLUDE_DIR}/unsupported_flag.hpp
    ${INCLUDE_DIR}/unsupported_option.hpp
)