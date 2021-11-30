#include <string>
#include <iostream>

using namespace std;

string newStr (string myStr, size_t foundValue, string& replaceStr)
{
    string newStr = "";
    string firstPart = "";
    string secondPart = "";

    size_t strLenght = myStr.size();
    for(size_t i = 0; i < strLenght; ++i)
    {
        if(i < foundValue)
        {
            firstPart += myStr[i];
        }
        else
        {
            secondPart += myStr[i];
        }
    }

    newStr = firstPart + replaceStr + secondPart;
    return newStr;
}

int main()
{
    string myString = "";
    string findStr = "";
    string replaceStr = "";

    getline(cin, myString);
    getline(cin, findStr);
    getline(cin, replaceStr);

    size_t found = 0;
    size_t foundStrSize = findStr.size();
    while(true)
    {
        found = myString.find(findStr);
        if(found != string::npos)
        {
            myString.erase(found, foundStrSize);

            ///cout << myString << endl;

            myString = newStr(myString, found, replaceStr);

            ///cout << myString << endl;
        }
        else
        {
            break;
        }
    }

    cout << myString << endl;
    return 0;
}


