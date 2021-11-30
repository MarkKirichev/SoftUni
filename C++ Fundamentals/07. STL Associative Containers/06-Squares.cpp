#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

void readInput(vector<int>& myVec)
{
    string s;
    getline(cin, s);
    stringstream myStream(s);

    string word;
    while(myStream >> word)
    {
        myVec.push_back(stoi(word));
    }
}

bool mySort(int x, int y)
{
    return x >= y;
}

void printSquares (vector<int>& myVec)
{
    size_t SIZE = myVec.size();
    --SIZE;
    ///for(size_t i = 0; i < SIZE; ++i)
    ///{
    ///    cout << myVec[i] << " ";
    ///}
    ///cout << myVec[SIZE] << endl;
    for(int elem: myVec)
    {
        cout << elem << " ";
    }
}

void getSquares (vector<int>& allNums, vector<int>& squareNums)
{
    size_t SIZE = allNums.size();
    int currentNum = 0;
    for(size_t i = 0; i < SIZE; ++i)
    {
        currentNum = allNums[i];
        for(int j = 1; ; ++j)
        {
            if((j*j) == currentNum)
            {
                squareNums.push_back(currentNum);
                break;
            }
            else if((j*j) > currentNum)
            {
                break;
            }
        }
    }
}

int main()
{
    vector<int> allNumbers;
    vector<int> squareNumbers;

    readInput(allNumbers);
    getSquares(allNumbers, squareNumbers);

    sort(squareNumbers.begin(), squareNumbers.end(), mySort);
    printSquares(squareNumbers);

    return 0;
}

