#include <iostream>
#include <string>
#include <vector>

using namespace std;

void readArray(vector<int>& numbers)
{
    string s;
    getline(cin, s, '\n');

    int current_num = 0;

    for(size_t i = 0; i < s.size(); ++i)
    {
        if(s[i] == ' ')
        {
            numbers.push_back(current_num);
            current_num = 0;
        }
        else
        {
            current_num *= 10;
            current_num += (s[i] - '0');
        }
    }

    numbers.push_back(current_num);
}

bool compareArrays(vector<int>& firstVec, vector<int>& secondVec)
{
    size_t i = firstVec.size();
    size_t j = secondVec.size();

    if(i != j)
    {
        return false;
    }

    for(size_t k = 0; k < i; ++k)
    {
        if(firstVec[k] != secondVec[k])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    vector<int> firstArray;
    vector<int> secondArray;

    readArray(firstArray);
    readArray(secondArray);

    bool compare = compareArrays(firstArray, secondArray);
    if(compare)
    {
        cout << "equal" << endl;
    }
    else
    {
        cout << "not equal" << endl;
    }
    return 0;
}
