#include "utils.hpp"
#include <minisat/core/Solver.h>

// Functions definitions
Minisat::Var toVar(int row, int column, int value) {
    return row * COLUMNS * VALUES + column * VALUES + value;
}
