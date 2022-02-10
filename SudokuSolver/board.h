#include <iostream>
using namespace std;

class board
{
private:
    int sudoku[9][9] = {
        {0, 0, 0, 8, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 4, 3},
        {5, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 7, 0, 8, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 2, 0, 0, 3, 0, 0, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 7, 5},
        {0, 0, 3, 4, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 6, 0, 0}};

public:
    void printSudoku();
    void insert(int row, int col, int value);
    bool isValid(int rowIndex, int colIndex, int value);
    bool solveSudoku(int rowIndex, int colIndex);
    bool getNextAvailable(int *rowIndex, int *colIndex);
    board() {}
};

void board::printSudoku()
{
    for (int row = 0; row < 9; row++)
    {
        if (row == 3 || row == 6)
        {
            cout << "_____________________________________\n";
        }
        else
        {
            cout << "-------------------------------------\n";
        }
        for (int col = 0; col < 9; col++)
        {
            if (col == 8)
            {
                cout << "| " << sudoku[row][col] << " |";
            }
            else
            {
                cout << "| " << sudoku[row][col] << ' ';
            }
        };
        cout << endl;
        if (row == 8)
        {
            cout << "-------------------------------------\n";
        };
    }
};

void board::insert(int row, int col, int value)
{
    sudoku[row][col] = value;
}

bool board::isValid(int rowIndex, int colIndex, int value)

{

    // Check duplicates for the given row index
    for (int c = 0; c < 9; c++)
    {
        if (sudoku[rowIndex][c] == value)
        {
            return false;
        }
    }

    // Check duplicates for the given column index
    for (int r = 0; r < 9; r++)
    {
        if (sudoku[r][colIndex] == value)
        {
            return false;
        }
    }

    // check for 3x3 grid
    int startRow = ((int)rowIndex / 3) * 3;
    int startCol = ((int)colIndex / 3) * 3;

    for (int r = startRow; r < startRow + 3; r++)
        for (int c = startCol; c < startCol + 3; c++)
            if (sudoku[r][c] == value)
            {
                return false;
            }

    return true;
}

bool board::getNextAvailable(int *row, int *col)
{
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
            if (sudoku[r][c] == 0)
            {
                *row = r;
                *col = c;
                return true;
            }
    return false;
}
bool board::solveSudoku(int rowIndex, int colIndex)
{
    if (!getNextAvailable(&rowIndex, &colIndex))
    {
        return true;
    }
    // base case
    if (colIndex == 9)
    {
        if (rowIndex == 9)
            return true;
        else
            return solveSudoku(rowIndex + 1, 0);
    };

    // Insert all possible values one at a time for each row
    for (int val = 1; val < 10; val++)
    {
        // if the position of the index is valu
        if (this->isValid(rowIndex, colIndex, val))
        {
            sudoku[rowIndex][colIndex] = val;
            if (solveSudoku(rowIndex, colIndex + 1))
            {
                return true;
            }
        }
        // not valid or could not solve then back track
        sudoku[rowIndex][colIndex] = 0;
    }
    return false;
}