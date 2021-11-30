#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printVecWords(vector<string>& myVec)
{
    size_t mySize = myVec.size();
    if(!mySize)
    {
        cout << endl;
        return;
    }

    for(size_t i = 0; i < myVec.size(); ++i)
    {
        cout << myVec[i] << " ";
    }

    cout << endl;
}

void printVecNumbers(vector<int>& myVec)
{
    size_t mySize = myVec.size();

    if(!mySize)
    {
        cout << 0 << endl;
        return;
    }

    long long all_sum = 0;

    for(size_t i = 0; i < myVec.size(); ++i)
    {
        all_sum += myVec[i];
    }

    cout << all_sum << endl;
}

int main()
{
    string s;
    string temporary = "";
    vector<string> wordVector;
    vector<int> numbersVector;

    getline(cin, s);
    size_t sizeOfString = s.size();

    int current_num = 0;
    bool flag = false;
    for(size_t i = 0; i < sizeOfString; ++i)
    {
        if(s[i] == ' ')
        {
            if(temporary != "")
            {
                wordVector.push_back(temporary);
                temporary = "";
            }
            else if(current_num)
            {
                if(flag)
                {
                    current_num = -current_num;
                }
                numbersVector.push_back(current_num);
                current_num = 0;
                flag = false;
            }
        }
        else if(s[i] >= '0' && s[i] <= '9')
        {
            current_num *= 10;
            current_num += (s[i] - '0');
        }
        else if(s[i] == '-')
        {
            flag = true;
        }
        else
        {
            temporary += s[i];
        }

    }

    if(temporary != "")
    {
        wordVector.push_back(temporary);
    }
    else if(current_num)
    {
        if(flag)
        {
            current_num = -current_num;
        }
        numbersVector.push_back(current_num);
    }

    printVecNumbers(numbersVector);
    printVecWords(wordVector);

    return 0;
}
