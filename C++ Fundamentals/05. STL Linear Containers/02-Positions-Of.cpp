#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> matrixNumbers;

    int x, y;
    cin >> x >> y;

    int nextNumber;
    for(int i = 0; i < x; ++i)
    {
        for(int j = 0; j < y; ++j)
        {
            cin >> nextNumber;
            matrixNumbers.push_back(nextNumber);
        }
    }

    int foundNumber = 0;
    cin >> foundNumber;

    bool flag = false;
    int z = x * y;
    for(int i = 0; i < z; ++i)
    {
        if(matrixNumbers[i] == foundNumber)
        {
            flag = true;
            cout << i / y << " " << i - y * (i / y) << endl;
        }
    }

    if(!(flag))
    {
        cout << "not found" << endl;
    }

    return 0;
}


