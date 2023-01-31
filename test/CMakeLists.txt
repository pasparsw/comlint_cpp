set(TARGET ComlintCppTests)

add_executable(${TARGET})

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/test_command_line_interface
)

target_sources(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/test_command_properties.cpp
    ${CMAKE_SOURCE_DIR}/src/parsed_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_parsed_command.cpp
    ${CMAKE_SOURCE_DIR}/src/interface_validator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_interface_validator.cpp
    ${CMAKE_SOURCE_DIR}/src/interface_helper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_interface_helper.cpp
    ${CMAKE_SOURCE_DIR}/src/parsed_command.cpp
    ${CMAKE_SOURCE_DIR}/src/command_line_interface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_command_line_interface/test_basic_features.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_command_line_interface/test_non_value_commands.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_command_line_interface/test_single_value_commands.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_command_line_interface/test_multiple_value_commands.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_command_line_interface/test_negative_cases.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_command_line_interface/test_non_command_based_interface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_command_line_interface/test_command_handlers.cpp
    ${CMAKE_SOURCE_DIR}/src/utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_utils.cpp
)

target_link_libraries(${TARGET} PRIVATE
    GTest::gtest_main
    GTest::gmock_main
)

add_test(${TARGET} ${TARGET})