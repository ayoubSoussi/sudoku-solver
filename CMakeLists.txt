cmake_minimum_required (VERSION 3.5)
project (sudoku-solver LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(MiniSat 2.2 REQUIRED)

add_executable(sudoku-solver
    main.cpp
)
target_link_libraries(sudoku-solver MiniSat::libminisat)
