#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

void turnWords(string& currentWord)
{
    size_t SIZE = currentWord.size();
    for(size_t i = 0; i < SIZE; ++i)
    {
        if(currentWord[i] >= 'A' && currentWord[i] <= 'Z')
        {
            currentWord[i] += 32;
        }
    }
}

int searchInMyVector(vector< pair<string, int> >& myVec, string& searchedWord)
{
    int SIZE = (int)myVec.size();
    for(int i = 0; i < SIZE; ++i)
    {
        if(myVec[i].first == searchedWord)
        {
            return i;
        }
    }
    return (-1);
}

void getWords(vector< pair<string, int> >& myVec, string& allWords)
{
    size_t SIZE = allWords.size();
    string current = "";
    int searchedValue = -1;
    pair<string, int> newPair;

    for(size_t i = 0; i < SIZE; ++i)
    {
        if(allWords[i] == ' ')
        {
            if(current != "")
            {
                turnWords(current);
                searchedValue = searchInMyVector(myVec, current);
                if(searchedValue == -1)
                {
                    newPair.first = current;
                    newPair.second = 1;
                    myVec.push_back(newPair);
                }
                else
                {
                    ++myVec[searchedValue].second;
                }
            }
            current = "";
            continue;
        }
        current += allWords[i];
    }
    if(current != "")
    {
        turnWords(current);
        searchedValue = searchInMyVector(myVec, current);
        if(searchedValue == (-1))
        {
            newPair.first = current;
            newPair.second = 1;
            myVec.push_back(newPair);
        }
        else
        {
            ++myVec[searchedValue].second;
        }
    }
}

void printOddOccurences(vector< pair<string, int> >& myVec)
{
    size_t SIZE = myVec.size();
    --SIZE;
    for(size_t i = 0; i < SIZE; ++i)
    {
        if((myVec[i].second) & 1)
        {
            cout << myVec[i].first << ", ";
        }
    }
    if((myVec[SIZE].second) & 1)
    {
        cout << myVec[SIZE].first << endl;
    }
    else
    {
        cout << endl;
    }
}

int main()
{
    vector< pair<string, int> > myVec;
    string input;
    getline(cin, input);

    getWords(myVec, input);
    printOddOccurences(myVec);
    return 0;
}


