set(TARGET ComlintCppTests)

add_executable(${TARGET})

target_sources(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/example_test.cpp
)

target_link_libraries(${TARGET} PRIVATE
    GTest::gtest_main
)

add_test(${TARGET} ${TARGET})