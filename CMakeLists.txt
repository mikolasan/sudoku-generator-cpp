cmake_minimum_required(VERSION 3.14)

project(sudoku_generator VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
    list.c
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

add_executable(test_list_bits ${SOURCE_FILES} test_list_bits.c)
add_test(NAME ListBitsTest COMMAND test_list_bits)

add_executable(test_figure_bits ${SOURCE_FILES} test_figure_bits.c)
add_test(NAME FigureBitsTest COMMAND test_figure_bits)

add_executable(test_pick_better ${SOURCE_FILES} test_pick_better.c)
add_test(NAME PickBetterTest COMMAND test_pick_better)

add_executable(test_deduce ${SOURCE_FILES} test_deduce.c)
add_test(NAME DeduceTest COMMAND test_deduce)

add_executable(test_solve_next ${SOURCE_FILES} test_solve_next.c)
add_test(NAME SolveNextTest COMMAND test_solve_next)

add_executable(test_make_puzzle ${SOURCE_FILES} test_make_puzzle.c)
add_test(NAME MakePuzzleTest COMMAND test_make_puzzle)

add_executable(test_solve_board ${SOURCE_FILES} test_solve_board.c)
add_test(NAME SolveBoardTest COMMAND test_solve_board)

add_executable(test_list ${SOURCE_FILES} test_list.c)
add_test(NAME ListTest COMMAND test_list)