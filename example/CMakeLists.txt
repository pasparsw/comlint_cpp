set(TARGET ExampleApp)

add_executable(${TARGET})

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_sources(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(${TARGET} PRIVATE
    ComlintCpp
)