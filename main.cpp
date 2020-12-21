// main.cpp:
#include <minisat/core/Solver.h>
#include <bits/stdc++.h>
#include <iostream>

#define ROWS       9
#define COLUMNS    9
#define VALUES     9

// declare variables
int board[ROWS][COLUMNS] = {0};

// Functions declarations
void read_input_board(int board[ROWS][COLUMNS]);
void display_sudoku_board(int board[ROWS][COLUMNS]);
void one_true(Minisat::Solver *solver, Minisat::vec<Minisat::Lit> const& literals);

// Rules
void add_rule1(Minisat::Solver *solver); // add predefined data as a rule
void add_rule2(Minisat::Solver *solver); // add 'each position contains one number' rule
void add_rule3(Minisat::Solver *solver); // add 'rows don't contain duplicate numbers' rule
void add_rule4(Minisat::Solver *solver); // add 'columns don't contain duplicate numbers' rule
void add_rule5(Minisat::Solver *solver); // add '3*3 boxes don't contain duplicate numbers' rule

// Functions definitions
Minisat::Var toVar(int row, int column, int value) {
    return row * COLUMNS * VALUES + column * VALUES + value;
}


int main() {
    using Minisat::mkLit;
    using Minisat::lbool;
    using Minisat::toLit;
    using Minisat::Var;

    Minisat::Solver solver;

    // add variables to the solver    
    for (int i = 0; i < ROWS*COLUMNS*VALUES; ++i) {
	static_cast<void>(solver.newVar());	
    }

	// Add predefined data in the board
	add_rule1(&solver);

    	// Each position contains one number
      	add_rule2(&solver);

	// Rows don't contain duplicate numbers
	add_rule3(&solver);

       	// Columns don't contain duplicate numbers
   	add_rule4(&solver);

	// the 9 boxes don't contain dusplicate numbers
	add_rule5(&solver);   
 	
	// Check for solution and retrieve model if found
    	auto sat = solver.solve();
    	if (sat) {
        	std::clog << "SAT\n"
                  << "Model found:\n";
	// Get result
	for (int row = 0; row < ROWS; ++row) {
        	for (int col = 0; col < COLUMNS; ++col) {
            		for (int val = 0; val < VALUES; ++val) {
                		if (solver.modelValue(toVar(row, col, val)).isTrue()) {
                    			board[row][col] = val + 1;
                    			break;
               			 }
           		 }
       		 }
   	}
       //std::clog << "UL := " << bd[0][0] << '\n';
       //std::clog << "DR := " << bd[8][8] << '\n';
       //std::clog << "ML := " << bd[4][0] << '\n';
       display_sudoku_board(board);
    } else {
        std::clog << "UNSAT\n";
        return 1;
    }
}

void read_input_board(int bd[ROWS][COLUMNS]){

    bd[0][3] = 2; bd[0][4] = 6; bd[0][6] = 7; bd[0][8] = 1;
    bd[1][0] = 6; bd[1][1] = 8; bd[1][4] = 7; bd[1][7] = 9;
    bd[2][0] = 1; bd[2][1] = 9; bd[2][5] = 4; bd[2][6] = 5;
    bd[3][0] = 8; bd[3][1] = 2; bd[3][3] = 1; bd[3][7] = 4; 
    bd[4][2] = 4; bd[4][3] = 6; bd[4][5] = 2; bd[4][6] = 9;
    bd[5][1] = 5; bd[5][5] = 3; bd[5][7] = 2; bd[5][8] = 8;
    bd[6][2] = 9; bd[6][3] = 3; bd[6][7] = 7; bd[6][8] = 4;
    bd[7][1] = 4; bd[7][4] = 5; bd[7][7] = 3; bd[7][8] = 6;
    bd[8][0] = 7; bd[8][2] = 3; bd[8][4] = 1; bd[8][5] = 8;
}

void add_rule1(Minisat::Solver *solver) {
    	read_input_board(board);

    	for (int row = 0; row < ROWS; ++row) {
        	for (int col = 0; col < COLUMNS; ++col) {
            		auto value = board[row][col];
            		if (value != 0) {
                		solver->addClause(Minisat::mkLit(toVar(row, col, value - 1)));
            		}
        	}
    	}
}

void add_rule2(Minisat::Solver *solver) {
	for (int row = 0; row < ROWS; ++row) {
    		for (int column = 0; column < COLUMNS; ++column) {
        		Minisat::vec<Minisat::Lit> literals;
        		for (int value = 0; value < VALUES; ++value) {
            			literals.push(Minisat::mkLit(toVar(row, column, value)));
       		 	}
        		one_true(solver, literals);
   		}
    	}
}

void add_rule3(Minisat::Solver *solver) {
	for (int row = 0; row < ROWS; ++row) {
 		for (int value = 0; value < VALUES; ++value) {
        		Minisat::vec<Minisat::Lit> lits_r;
       			for (int column = 0; column < COLUMNS; ++column) {
            			lits_r.push(Minisat::mkLit(toVar(row, column, value)));
        		}
        		one_true(solver, lits_r);
    		}
    	}
}

void add_rule4(Minisat::Solver *solver) {
	for (int column = 0; column < COLUMNS; ++column) {
 		for (int value = 0; value < VALUES; ++value) {
        		Minisat::vec<Minisat::Lit> lits_c;
        		for (int row = 0; row < ROWS; ++row) {
            			lits_c.push(Minisat::mkLit(toVar(row, column, value)));
        		}
        		one_true(solver, lits_c);
    		}
    	}
}

void add_rule5(Minisat::Solver *solver) {
	for (int row = 0; row < ROWS; row += 3) {
    		for (int column = 0; column < COLUMNS; column += 3) {
        		for (int value = 0; value < VALUES; ++value) {
            			Minisat::vec<Minisat::Lit> lits;
            			for (int rb = 0; rb < 3; ++rb) {
                			for (int cb = 0; cb < 3; ++cb) {
                    				lits.push(Minisat::mkLit(toVar(row + rb, column + cb, value)));
                			}
            			}
            			one_true(solver, lits);
        		}
    		}
    	}
}


void display_sudoku_board(int bd[ROWS][COLUMNS]) {
	for (int r = 0; r < ROWS; r++) {
		std::clog << "|";
		for (int c = 0; c < COLUMNS; c++) {
			std::clog << bd[r][c] << "|";
		}
		std::clog << "\n";
	}
}

void one_true(Minisat::Solver *solv, Minisat::vec<Minisat::Lit> const& literals) {
    solv->addClause(literals);
    for (size_t i = 0; i < literals.size(); ++i) {
        for (size_t j = i + 1; j < literals.size(); ++j) {
            solv->addClause(~literals[i], ~literals[j]);
        }
    }
}


