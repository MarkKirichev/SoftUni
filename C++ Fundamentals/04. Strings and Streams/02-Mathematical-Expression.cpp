#include <iostream>
#include <string>

using namespace std;

bool checkParentheses(string& myExp)
{
    int counter = 0;
    size_t mySize = myExp.size();

    for(size_t i = 0; i < mySize; ++i)
    {
        if(counter < 0)
        {
            return false;
        }

        if(myExp[i] == '(')
        {
            ++counter;
        }
        else if(myExp[i] == ')')
        {
            --counter;
        }
    }

    if(!counter)
    {
        return true;
    }

    return false;
}

int main()
{
    string myExpression;
    getline(cin, myExpression, '\n');

    if(checkParentheses(myExpression))
    {
        cout << "correct" << endl;
    }
    else
    {
        cout << "incorrect" << endl;
    }
    return 0;
}
