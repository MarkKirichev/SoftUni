#include <iostream>
#include <string>
using namespace std;

const char smallBracket = '(';
const char midBracket = '[';
const char bigBracket = '{';

bool isTrue = true;

void smallBrackets(string& s)
{
    size_t found = s.find(smallBracket);
    if(found == string::npos)
    {
        return;
    }

    size_t myStrSize = s.size();
    for(size_t i = 0; i < s.size(); ++i)
    {
        if(s[i] == '(')
        {
            for(size_t j = (i+1); j < s.size(); ++j)
            {
                if(s[j] == '[' || s[j] == ']' || s[j] == '{' || s[j] == '}')
                {
                    isTrue = false;
                    return;
                }
                else if(s[j] == ')')
                {
                    s.erase(i, 1);
                    s.erase(j-1, 1);
                    smallBrackets(s);
                    return;
                }
            }
            isTrue = false;
            return;
        }
    }

}

void midBrackets(string& s)
{
    size_t found = s.find(midBracket);
    if(found == string::npos)
    {
        return;
    }

    size_t myStrSize = s.size();
    for(size_t i = 0; i < s.size(); ++i)
    {
        if(s[i] == '[')
        {
            for(size_t j = (i+1); j < s.size(); ++j)
            {
                if(s[j] == '{' || s[j] == '}')
                {
                    isTrue = false;
                    return;
                }
                else if(s[j] == ']')
                {
                    s.erase(i, 1);
                    s.erase(j-1, 1);
                    midBrackets(s);
                    return;
                }
            }
            isTrue = false;
            return;
        }
    }

}

void bigBrackets(string& s)
{
    size_t found = s.find(bigBracket);
    if(found == string::npos)
    {
        return;
    }

    size_t myStrSize = s.size();
    for(size_t i = 0; i < s.size(); ++i)
    {
        if(s[i] == '{')
        {
            for(size_t j = (i+1); j < s.size(); ++j)
            {
                if(s[j] == '}')
                {
                    s.erase(i, 1);
                    s.erase(j-1, 1);
                    bigBrackets(s);
                    return;
                }
            }
            isTrue = false;
            return;
        }
    }
}

int main()
{
    string bracks = "";
    getline(cin, bracks);

    smallBrackets(bracks);
    if(!isTrue)
    {
        cout << "invalid" << endl;
        return 0;
    }

    midBrackets(bracks);
    if(!isTrue)
    {
        cout << "invalid" << endl;
        return 0;
    }

    bigBrackets(bracks);
    if(!isTrue)
    {
        cout << "invalid" << endl;
        return 0;
    }

    else
    {
        cout << "valid" << endl;
        return 0;
    }
}

