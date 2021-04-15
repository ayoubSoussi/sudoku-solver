// main.cpp:
#include "main.hpp"
#include "utils.hpp"
#include <minisat/core/Solver.h>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>


// declare variables
int board[ROWS][COLUMNS] = {0};
int example_nb;

int main(int argc, char** argv) {
	using Minisat::mkLit;
    	using Minisat::lbool;
    	using Minisat::toLit;
    	using Minisat::Var;
	
	Minisat::Solver solver;

	// read input filename
	if (argc > 1) example_nb = atoi(argv[1]);

    	// add variables to the solver    
    	for (int i = 0; i < ROWS*COLUMNS*VALUES; ++i) {
		static_cast<void>(solver.newVar());	
    	}

	// Read input board data
     	if (!read_input_board(board)) return 1;

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
        	std::clog << "[SUCCESS] The sudoku board has a solution !\n";

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

		// display final board
       		display_sudoku_board(board);
    	} else {
        	std::clog << "[FAILED] The sudoku board doesn't have a solution !\n";
        	return 1;
    	}
}

bool read_input_board(int bd[ROWS][COLUMNS]){
	
	std::ifstream infile("input.txt");
    	std::string line;
	char cc;
	
	// search for example number
	while (std::getline(infile, line)) {
		std::istringstream is(line);
		int a;
		
		if (!(is >> a)) continue;
		if (a != example_nb) continue;

		break;
	}

	for (int r = 0; r < ROWS; r++) {
		if (!std::getline(infile, line)) {
		    // error
		    if (r == 0) std::clog << "Error : No example with the number specified\n";
		    else std::clog << "Error : Example is not complete, missing line(s)\n";
		    
		    return false;
		}

		std::istringstream iss(line);
		for (int c = 0; c < COLUMNS; c++) {
			if (iss.get(cc) && iss.get(cc)) {
				if (cc >= '1' && cc <= '9') bd[r][c] = cc - '0';
			}
			else {
				std::clog << "Error : Columns missing in line " << r+1 << "of example n°" << example_nb << "\n";
				return false;
			}
    		}
	}

	return true;
}

void add_rule1(Minisat::Solver *solver) {

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
