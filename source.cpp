#include <iostream>
#include "board.h"

using namespace std;

int main(void)
{
    board sudoku;
    sudoku.solveSudoku(0, 0);
    sudoku.printSudoku();
    return 0;
}