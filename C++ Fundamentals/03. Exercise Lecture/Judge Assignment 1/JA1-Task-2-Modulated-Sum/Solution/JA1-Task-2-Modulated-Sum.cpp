#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int> > arrays;

    for (int i = 0; i < n; i++)
    {
        vector<int> currentArr;

        for (int col = 0; col < m; col++)
        {
            int value;
            cin >> value;
            currentArr.push_back(value);
        }

        arrays.push_back(currentArr);
    }

    int modulo;
    cin >> modulo;

    vector<int> modulatedSumArr;
    for (int column = 0; column < m; column++)
    {
        modulatedSumArr.push_back(0);
        for (int arrInd = 0; arrInd < arrays.size(); arrInd++)
        {
            modulatedSumArr[column] += arrays[arrInd][column];
        }
    }

    for (int i = 0; i < m; i++)
    {
        cout << modulatedSumArr[i] % modulo << " ";
    }

    return 0;
}
