#include <iostream>
#include <vector>

using namespace std;

void printBoard(const vector<vector<int> >& board) {
    int N = board.size();
    for (int i = 0; i < N; i++) {
        if (i % 3 == 0 && i != 0) {
            cout << "- - - - - - - - - - - -" << endl;
        }

        for (int j = 0; j < N; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << " | ";
            }

            if (j == N - 1) {
                cout << board[i][j];
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

bool isValid(const vector<vector<int> >& board, int row, int col, int num) {
    int N = board.size();
    // Check row and column
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool findEmptyLocation(const vector<vector<int> >& board, int& row, int& col) {
    int N = board.size();
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                return true; // Empty location found
            }
        }
    }
    return false; // No empty location found
}

bool solveSudoku(vector<vector<int> >& board) {
    int row, col;
    if (!findEmptyLocation(board, row, col)) {
        return true; // Puzzle solved
    }

    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board)) {
                return true;
            }

            board[row][col] = 0; // Backtrack
        }
    }

    return false; // No solution exists
}

int main() {
    int N;
    cout << "Enter the size of the Sudoku puzzle grid: ";
    cin >> N;

    vector<vector<int> > board(N, vector<int>(N));

    cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";
    for (int i = 0; i < N; i++) {
        cout << "Row " << (i + 1) << ": ";
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    cout << "\nSudoku puzzle:" << endl;
    printBoard(board);
    cout << endl << "Solving..." << endl;
    if (solveSudoku(board)) {
        cout << "Solution:" << endl;
        printBoard(board);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}
