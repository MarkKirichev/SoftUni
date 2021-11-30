#include <iostream>
#include <sstream>
#include <string>
#include <set>

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

bool isSmallWord (string& myWord)
{
    if(myWord.size() < 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}



int main()
{
    string s;
    getline(cin, s);
    set<string> mySet;

    stringstream MyStream(s);
    string word;
    while(MyStream >> word)
    {
        turnWords(word);
        if(isSmallWord(word))
        {
            if(mySet.find(word) == mySet.end())
            {
                mySet.insert(word);
            }
        }
    }

    string finalStr = "";
    for(set<string>::iterator it = mySet.begin(); it != mySet.end(); ++it)
    {
        finalStr += *it;
        finalStr += ", ";
    }

    size_t SIZE = finalStr.size();
    SIZE -= 2;
    for(size_t i = 0; i < SIZE; ++i)
    {
        cout << finalStr[i];
    }
    return 0;
}


