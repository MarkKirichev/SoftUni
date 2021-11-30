#include<iostream>
using namespace std;

const short MAX_ROWS = 20;
const short MAX_COLS = 20;

char matrix[MAX_ROWS][MAX_COLS];

void fillDfs(char fillChar, char paintableChar, int row, int col)
{
    if (row < 0 || row >= MAX_ROWS || col < 0 || col >= MAX_COLS || matrix[row][col] != paintableChar)
    {
        return;
    }

    matrix[row][col] = fillChar;

    // fill starting from the neighboring cells, "clockwise"
    fillDfs(fillChar, paintableChar, row - 1, col);
    fillDfs(fillChar, paintableChar, row, col + 1);
    fillDfs(fillChar, paintableChar, row + 1, col);
    fillDfs(fillChar, paintableChar, row, col - 1);
}

int main() {
    int rows, cols;
    cin >> rows >> cols;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            cin >> matrix[row][col];
        }
    }

    char fillChar;
    cin >> fillChar;

    int startRow, startCol;
    cin >> startRow >> startCol;

    char startChar = matrix[startRow][startCol];

    fillDfs(fillChar, startChar, startRow, startCol);

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            cout << matrix[row][col];
        }

        cout << endl;
    }

    return 0;
}
