set(TARGET ComlintCppTests)

add_executable(${TARGET})

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_sources(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/test_interface_validator.cpp
)

find_library(ComlintCpp NAMES ComlintCpp HINTS ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(${TARGET} PRIVATE
    GTest::gtest_main
    ComlintCpp
)

add_test(${TARGET} ${TARGET})

install(DIRECTORY ${CMAKE_BINARY_DIR}/bin/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE} FILES_MATCHING PATTERN "*.dll")