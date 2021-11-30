#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

void readInput(vector<double>& myVec)
{
    string s;
    getline(cin, s);
    stringstream myStream(s);

    string word;
    while(myStream >> word)
    {
        myVec.push_back(stod(word));
    }
}

bool mySort(double x, double y)
{
    return x >= y;
}

int main()
{
    vector<double> myVec;
    readInput(myVec);

    sort(myVec.begin(), myVec.end(), mySort);

    size_t SIZE = myVec.size();
    if(SIZE == 1)
    {
        cout << myVec[0] << endl;
        return 0;
    }
    else if(SIZE == 2)
    {
        cout << myVec[0] << " " << myVec[1] << endl;
        return 0;
    }
    else
    {
        cout << myVec[0] << " " <<  myVec[1] << " " << myVec[2] << endl;
        return 0;
    }
}


