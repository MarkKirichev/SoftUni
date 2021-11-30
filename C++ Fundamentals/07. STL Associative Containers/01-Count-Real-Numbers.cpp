#include <iostream>
#include <map>
#include <sstream>

using namespace std;

int main()
{
    map<double, int> countNums;
    string s, word;

    getline(cin, s, '\n');
    stringstream myStream(s);
    while(myStream >> word)
    {
        ++countNums[stod(word)];
    }

    for(map<double, int>::iterator it = countNums.begin(); it != countNums.end(); ++it)
    {
        cout << it -> first << " -> " << it -> second << endl;
    }
    return 0;
}

