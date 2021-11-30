#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool mySort(int x, int y)
{
    return x > y;
}

int numberFromStr(string s)
{
    size_t sizeOfStr = s.size();
    int currentNum = 0;

    for(size_t i = 0; i < sizeOfStr; ++i)
    {
        if(s[i] >= '0' && s[i] <= '9')
        {
            currentNum *= 10;
            currentNum += (s[i] - '0');
        }
    }

    return currentNum;
}

int main()
{
    string s;
    string temporary = "";
    getline(cin, s);

    vector<int> myArray;

    size_t mySize = s.size();
    temporary += s[0];

    for(size_t i = 1; i < mySize; ++i)
    {
        if (s[i] == ' ')
        {
            if(temporary != "")
            {
                myArray.push_back(numberFromStr(temporary));
                temporary = "";
            }
        }
        else
        {
            temporary += s[i];
        }
    }

    if(temporary != "")
    {
        myArray.push_back(numberFromStr(temporary));
    }

    if(myArray.size() == 0)
    {
        cout << 0 << endl;
        return 0;
    }

    sort(myArray.begin(), myArray.end(), mySort);
    cout << myArray[0] << endl;
    return 0;
}
