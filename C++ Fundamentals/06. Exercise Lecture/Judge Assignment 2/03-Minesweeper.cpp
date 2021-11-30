#include <iostream>
#include <string>
#include <vector>
#include <queue>

//5 5
//.....
//...!.
//.....
//.....
//.....

//00111
//00111
//00111
//00000
//00000

std::vector<std::vector<char>> readInput()
{
    std::vector<std::vector<char>> matrix;

    int rows = 0;
    int cols = 0;
    std::cin >> rows >> cols;
    matrix.resize(rows);
    for(int i = 0; i < rows; ++i)
    {
        matrix[i].resize(cols);
        for(int j = 0; j < cols; ++j)
        {
            std::cin >> matrix[i][j];
        }
    }

    return matrix;
}

void findAllMines(const std::vector<std::vector<char>> & matrix,
                  std::queue<int> & outRows,
                  std::queue<int> & outCols)
{
    const int ROWS = matrix.size();
    for(int i = 0; i < ROWS; ++i)
    {
        const int COLS = matrix[i].size();
        for(int j = 0; j < COLS; ++j)
        {
            if('!' == matrix[i][j]) //we found a mine!
            {
                outRows.push(i);
                outCols.push(j);
            }
        }
    }
}

bool isInBound(const std::vector<std::vector<int>> & matrix,
               const int row,
               const int col)
{
    if(row >= 0 && row < (int)matrix.size() && col >= 0 && col < (int)matrix[row].size())
    {
        return true;
    }

    return false;
}

void denonateSingleMine(std::vector<std::vector<int>> & outputMatrix,
                        const int row,
                        const int col)
{

    //upper left
    if(isInBound(outputMatrix, row - 1, col - 1))
    {
        outputMatrix[row - 1][col - 1] += 1;
    }

    //top
    if(isInBound(outputMatrix, row - 1, col))
    {
        outputMatrix[row - 1][col] += 1;
    }

    //upper right
    if(isInBound(outputMatrix, row - 1, col + 1))
    {
        outputMatrix[row - 1][col + 1] += 1;
    }

    //right
    if(isInBound(outputMatrix, row, col + 1))
    {
        outputMatrix[row][col + 1] += 1;
    }

    //bottom right
    if(isInBound(outputMatrix, row + 1, col + 1))
    {
        outputMatrix[row + 1][col + 1] += 1;
    }

    //bottom
    if(isInBound(outputMatrix, row + 1, col))
    {
        outputMatrix[row + 1][col] += 1;
    }

    //bottom left
    if(isInBound(outputMatrix, row + 1, col - 1))
    {
        outputMatrix[row + 1][col - 1] += 1;
    }

    //left
    if(isInBound(outputMatrix, row, col - 1))
    {
        outputMatrix[row][col - 1] += 1;
    }

    //center
    if(isInBound(outputMatrix, row, col))
    {
        outputMatrix[row][col] += 1;
    }
}

void detonateAllMines(std::vector<std::vector<int>> & outputMatrix,
                      std::queue<int> & minesRows,
                      std::queue<int> & minesCols)
{
    int currRow = 0;
    int currCol = 0;
    while(!minesRows.empty())
    {
        currRow = minesRows.front();
        minesRows.pop();

        currCol = minesCols.front();
        minesCols.pop();

        denonateSingleMine(outputMatrix, currRow, currCol);
    }
}

void printOutput(const std::vector<std::vector<int>> & outputMatrix)
{
    for(auto & row : outputMatrix)
    {
        for(const int elem : row)
        {
            std::cout << elem;
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::vector<std::vector<char>> matrix = readInput();
    std::vector<std::vector<int>> outputMatrix(matrix.size(),
                                       std::vector<int>(matrix[0].size(), 0));

    std::queue<int> minesRows;
    std::queue<int> minesCols;

    findAllMines(matrix, minesRows, minesCols);
    detonateAllMines(outputMatrix, minesRows, minesCols);
    printOutput(outputMatrix);

	return 0;
}
