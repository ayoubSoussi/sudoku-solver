cmake_minimum_required (VERSION 3.5)
project (sudoku-solver LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(MiniSat 2.2 REQUIRED)

add_executable(sudoku-solver
    src/main.cpp src/utils.cpp
)

add_executable(sudoku-solver-test tests/sudoku-test.cpp src/utils.cpp)

target_link_libraries(sudoku-solver MiniSat::libminisat)
target_link_libraries(sudoku-solver-test MiniSat::libminisat)
