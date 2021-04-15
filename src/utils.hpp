#include <minisat/core/Solver.h>

#define ROWS       9
#define COLUMNS    9
#define VALUES     9

// Functions definitions
Minisat::Var toVar(int row, int column, int value);
