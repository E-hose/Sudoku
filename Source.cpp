#include <iostream>
using namespace std;


const int ROW = 9;
const int COL = 9;



void print(int[][COL]);
bool isSafe(int[][COL], int, int, int);
bool solve(int[][COL], int, int);


bool isSafe(int g[][COL], int row,
	int col, int num)
{
	//check for duplicate numbers in row
	for (int i = 0; i <= 8; i++)
		if (g[row][i] == num)
			return false;

	//check for duplicate number in col
	for (int i = 0; i <= 8; i++)
		if (g[i][col] == num)
			return false;

	//check duplicate number in 3 by 3 matrix
	int startRow = row - row % 3,
		startCol = col - col % 3;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (g[i + startRow][j + startCol] == num)
				return false;

	return true;
}


bool solve(int g[][COL], int row, int col)
{
	//to prevent further backtracking
    if (row == ROW - 1 && col == COL)
        return true;

	//move to the next row
    if (col == ROW) {
        row++;
        col = 0;
    }

	//move to next empty cell if current cell is full
    if (g[row][col] > 0)
        return solve(g, row, col + 1);

	//make assumptions and check safety of grid
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(g, row, col, num))
        {
            g[row][col] = num;

			//check for the next possibility with the next column
            if (solve(g, row, col + 1))
                return true;
        }

		//assumption may be wrong, so empty the cell
        g[row][col] = 0;
    }
    return false;
}

//print the answer
void print(int g[][COL]) {


	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			//print out each element
			cout << g[i][j] << " ";
		}
		cout << endl;
	}

}

int main()
{


	int input;
	int grid[ROW][COL];

/* Testing purpose
	int grid[ROW][COL]= { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
					   { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
					   { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
					   { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
					   { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
					   { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
					   { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
					   { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
					   { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
*/
	//user inputs a grid
	cout << "Enter the sudoku grid to generate the answer" << endl;

	
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cin >> input;
			grid[i][j] = input;
		}
	}
	

	cout << "\n\n";

	
	if (solve(grid, 0, 0))
	{
		cout << "ANSWER...\n" << endl;
		print(grid);
	}

	else
		cout << "no solution exists" << endl;



	cin.get();
	cin.ignore();
	return 0;
}




