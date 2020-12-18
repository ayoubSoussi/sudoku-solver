cmake_minimum_required (VERSION 3.5)
project (minisat-example LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(MiniSat 2.2 REQUIRED)

add_executable(minisat-example
    main.cpp
)
target_link_libraries(minisat-example MiniSat::libminisat)
