#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*---------------------------------------------------------------------------*/

// N is the size of the 2D matrix   N*N
#define N 9

/*---------------------------------------------------------------------------*/

void sudoku_print(int arr[N][N]);
int sudoku_solve(int grid[N][N], int row, int col);

/*---------------------------------------------------------------------------*/
