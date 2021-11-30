#include <iostream>
#include <vector>
#include <string>

using namespace std;

void pushItemsInVector (vector<int>& myVector, int size)
{
    string s;
    bool flag = false;
    getline(cin, s);

    size_t mySize = s.size();
    int currentNum = 0;
    short totalNumsInRow = 0;
    for(size_t i = 0; i < mySize; ++i)
    {
        if(s[i] == ' ')
        {
            ++totalNumsInRow;
            if(flag)
            {
                currentNum = -currentNum;
                flag = false;
            }
            myVector.push_back(currentNum);
        }
        else if(s[i] == '-')
        {
            flag = true;
        }
        else
        {
            currentNum *= 10;
            currentNum += (s[i] - '0');
        }
    }

    myVector.push_back(currentNum);
    ++totalNumsInRow;

    ///cout << "Yes" << endl;

    --size;
    if(size == 0)
    {
        return;
    }

    int x;
    for(int i = 0; i < size; ++i)
    {
        for(short j = 0; j < totalNumsInRow; ++j)
        {
            cin >> x;
            myVector.push_back(x);
        }
    }
}

bool equalVectors(vector<int>& vecFirst, vector<int>& vecSecond)
{
    size_t mySize = vecFirst.size();
    for(size_t i = 0; i < mySize; ++i)
    {
        if(vecFirst[i] != vecSecond[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    vector<int> firstVec;
    vector<int> secondVec;

    int x, y;
    cin >> x;
    cin.ignore();
    pushItemsInVector(firstVec, x);

    ///cout << "Yes" << endl;

    cin >> y;
    cin.ignore();

    if(x != y)
    {
        cout << "not equal" << endl;
        return 0;
    }

    pushItemsInVector(secondVec, y);

    if(equalVectors(firstVec, secondVec))
    {
        cout << "equal" << endl;
    }
    else
    {
        cout << "not equal" << endl;
    }
    return 0;
}

