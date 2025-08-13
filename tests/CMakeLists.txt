file(GLOB TEST_SOURCES *.c utils/*.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CUNIT REQUIRED cunit)

add_executable(run_tests ${TEST_SOURCES})

target_include_directories(run_tests PRIVATE
    ${CUNIT_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests
)

target_link_libraries(run_tests dsa_lib ${CUNIT_LIBRARIES})

target_link_options(run_tests PRIVATE
    -Wl,--wrap=malloc
    -Wl,--wrap=calloc
    -Wl,--wrap=realloc
)

# Copy test_data folder to build folder
add_custom_command(TARGET run_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/tests/test_data
            ${CMAKE_CURRENT_BINARY_DIR}/test_data
)

# Register for CTest
add_test(NAME all_tests COMMAND run_tests)
