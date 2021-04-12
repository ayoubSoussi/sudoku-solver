# sudoku-solver [![CircleCI](https://circleci.com/gh/circleci/circleci-docs.svg?style=shield)](https://circleci.com/gh/circleci/circleci-docs)

A Minisat-based solver for 9*9 sudoku boards.

### How does it work ?
The solver reads the input incomplete sudoku board from an input file, and after solving, it provides the complete sudoku board.
To solve the sudoku board, the game is transformed into boolean problem (expressed by boolean equations) and then the program uses Minisat to solve those boolean equations.

### Prerequisites
- Linux machine.
- CMake.
- [Minisat](http://minisat.se/) : a SAT solver.

To install Minisat :
```shell
git clone https://github.com/master-keying/minisat.git
cd minisat
mkdir build && cd build
cmake ..
make
make install
```

### How to use it ?
You can easily use the sudoku solver by running these few commands.
```shell
git clone https://github.com/ayoubSoussi/sudoku-solver.git
cd sudoku-solver/example
cmake ..
make
./sudoku-solver X
```
The X is the ID number of the sudoku board that you want to solve, and this ID exists right before the sudoku board in the ```input.txt``` file.

If you need for example to solve the following sudoku problem :
```shell
|.|.|.|2|6|.|7|.|1|
|6|8|.|.|7|.|.|9|.|
|1|9|.|.|.|4|5|.|.|
|8|2|.|1|.|.|.|4|.|
|.|.|4|6|.|2|9|.|.|
|.|5|.|.|.|3|.|2|8|
|.|.|9|3|.|.|.|7|4|
|.|4|.|.|5|.|.|3|6|
|7|.|3|.|1|8|.|.|.|
```
Go to the end of the file ```input.txt``` and add a line containing an ID, for example 8, and add another 9 lines containing your sudoku board.
Then you can solve it easily by executing the solver :
```shell
./sudoku-solver 8
```
## NB
- Make sure to execute the solver in the same directory of the input.txt file.
- Respect the format of the ```input.txt``` file provided in the ```example``` directory.
- The ID of your sudoku board should be unique in the ```input.txt``` file (no IDs duplication), otherwise the solver will end up solving another sudoku board.

## Demo video

[My sudoku-solver on Youtube](https://www.youtube.com/watch?v=GTE29LMTZjA)
### References
- [Solving Sudoku with Boolean Algebra by Abu Sayed Chowdhury and Suraiya Akhter](https://www.researchgate.net/publication/258652094_Solving_Sudoku_using_Boolean_Algebra)
- [A SAT-based Sudoku Solver by Tjark Weber](https://www.lri.fr/~conchon/PFA/PROJET/A_SAT-based_Sudoku_solver.pdf)
