#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main()
{
    vector<int> myVec;
    string input;
    getline(cin, input);

    istringstream s(input);
    int n;
    while(s >> n)
    {
        myVec.push_back(n);
    }

    sort(myVec.begin(), myVec.end());

    size_t SIZE = myVec.size();
    --SIZE;
    for(size_t i = 0; i < SIZE; ++i)
    {
        cout << myVec[i] << " <= ";
    }
    cout << myVec[SIZE] << endl;
    return 0;
}


