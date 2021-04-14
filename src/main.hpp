#include <minisat/core/Solver.h>

#define ROWS       9
#define COLUMNS    9
#define VALUES     9

// Functions declarations
bool read_input_board(int board[ROWS][COLUMNS]);
void display_sudoku_board(int board[ROWS][COLUMNS]);
void one_true(Minisat::Solver *solver, Minisat::vec<Minisat::Lit> const& literals);

// Rules
void add_rule1(Minisat::Solver *solver); // add predefined data as a rule
void add_rule2(Minisat::Solver *solver); // add 'each position contains one number' rule
void add_rule3(Minisat::Solver *solver); // add 'rows don't contain duplicate numbers' rule
void add_rule4(Minisat::Solver *solver); // add 'columns don't contain duplicate numbers' rule
void add_rule5(Minisat::Solver *solver); // add '3*3 boxes don't contain duplicate numbers' rule

Minisat::Var toVar(int row, int column, int value);
