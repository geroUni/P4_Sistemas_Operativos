#ifndef SUDOKU_H
#define SUDOKU_H

#define N 9

void sudoku_print(int arr[N][N]);
int sudoku_solve(int grid[N][N], int row, int col);

#endif /* SUDOKU_H */
