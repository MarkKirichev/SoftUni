#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool mySort(string x, string y)
{
    size_t size_x = x.size();
    size_t size_y = y.size();

    if(size_x != size_y)
    {
        return size_x > size_y;
    }
    return x < y;
}

string noiseFromStr(string& s)
{
    size_t sizeOfStr = s.size();
    string currentStr = "";

    for(size_t i = 0; i < sizeOfStr; ++i)
    {
        if(!(s[i] >= '0' && s[i] <= '9'))
        {
            currentStr += s[i];
        }
    }

    return currentStr;
}

int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    
    string s;
    string temporary = "";
    string newNoise = "";
    getline(cin, s);

    vector<string> myArray;

    size_t mySize = s.size();
    temporary += s[0];

    for(size_t i = 1; i < mySize; ++i)
    {
        if (s[i] == ' ')
        {
            if(temporary != "")
            {
                newNoise = noiseFromStr(temporary);
                if(newNoise != " ")
                {
                    myArray.push_back(newNoise);
                }
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
        myArray.push_back(noiseFromStr(temporary));
    }

    sort(myArray.begin(), myArray.end(), mySort);

    if(myArray[0] == "")
    {
        cout << "no noise" << endl;
        return 0;
    }

    cout << myArray[0] << endl;
    return 0;
}
