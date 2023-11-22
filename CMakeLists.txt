cmake_minimum_required(VERSION 3.14)

project(sudoku_generator VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
    generator.c
)

add_executable(generator ${SOURCE_FILES} main.c)


enable_testing()

add_executable(test_make_array ${SOURCE_FILES} test_make_array.c)
add_test(NAME MakeArrayTest COMMAND test_make_array)

add_executable(test_shuffle_array ${SOURCE_FILES} test_shuffle_array.c)
add_test(NAME ShuffleArrayTest COMMAND test_shuffle_array)

add_executable(test_pos_for ${SOURCE_FILES} test_pos_for.c)
add_test(NAME PosForTest COMMAND test_pos_for)

add_executable(test_axis_missing ${SOURCE_FILES} test_axis_missing.c)
add_test(NAME AxisMissingTest COMMAND test_axis_missing)