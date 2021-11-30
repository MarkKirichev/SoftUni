#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool mySort(int x, int y)
{
    return x > y;
}

void pushIntoQueue(queue<int>& myQueue, string& rail)
{
    size_t mySize = rail.size();

    int currentNum = 0;
    for(size_t i = 0; i < mySize; ++i)
    {
        if(rail[i] == ' ')
        {
            if(currentNum)
            {
                myQueue.push(currentNum);
                currentNum = 0;
            }
        }
        else
        {
            currentNum *= 10;
            currentNum += (rail[i] - '0');
        }
    }
    if(currentNum)
    {
        myQueue.push(currentNum);
    }
}

void getVector (vector<int>& myVec, queue<int> q1, queue<int> q2)
{
    size_t size = q1.size();
    for(size_t i = 0; i < size; ++i)
    {
        myVec.push_back(q1.front());
        q1.pop();
    }
    size = q2.size();
    for(size_t i = 0; i < size; ++i)
    {
        myVec.push_back(q2.front());
        q2.pop();
    }

    sort(myVec.begin(), myVec.end(), mySort);
}

void printVec(vector<int>& myVec)
{
    for(vector<int>::iterator it = myVec.begin(); it != myVec.end(); ++it)
    {
        cout << *it << " ";
    }
}

string reverse(string const &s)
{
    string rev;
    for (int i = s.size() - 1; i >= 0; --i)
    {
        rev = rev.append(1, s[i]);
    }

    return rev;
}

int main()
{
    queue<char> myQueue;
    queue<int> queueFirst;
    queue<int> queueSecond;
    vector<int> myVector;

    size_t mySize = 0;

    string s, r;
    getline(cin, s);
    getline(cin, r);

    pushIntoQueue(queueFirst, s);
    pushIntoQueue(queueSecond, r);

    getVector(myVector, queueFirst, queueSecond);

    while(queueFirst.size() > 0 && queueSecond.size() > 0)
    {
        if(queueFirst.front() > queueSecond.front())
        {
            myQueue.push('A');
            queueFirst.pop();
        }
        else
        {
            myQueue.push('B');
            queueSecond.pop();
        }
    }
    if(queueFirst.size())
    {
        mySize = queueFirst.size();
        for(size_t i = 0; i < mySize; ++i)
        {
            myQueue.push('A');
        }
    }
    if(queueSecond.size())
    {
        mySize = queueSecond.size();
        for(size_t i = 0; i < mySize; ++i)
        {
            myQueue.push('B');
        }
    }

    mySize = myQueue.size();
    s = "";
    for(size_t i = 0; i < mySize; ++i)
    {
        s += myQueue.front();
        myQueue.pop();
    }
    cout << reverse(s);
    cout << endl;
    printVec(myVector);
    return 0;
}
