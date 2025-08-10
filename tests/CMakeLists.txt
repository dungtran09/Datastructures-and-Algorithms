file(GLOB TEST_SOURCES *.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CUNIT REQUIRED cunit)

add_executable(run_tests ${TEST_SOURCES})

target_include_directories(run_tests PRIVATE ${CUNIT_INCLUDE_DIRS})
target_link_libraries(run_tests dsa_lib ${CUNIT_LIBRARIES})

add_test(NAME AllTests COMMAND run_tests)

target_link_options(run_tests PRIVATE
    -Wl,--wrap=malloc
    -Wl,--wrap=calloc
    -Wl,--wrap=realloc
)

