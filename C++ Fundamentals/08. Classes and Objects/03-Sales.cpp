#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    map<string, double> myMap;

    int n;
    cin >> n;

    string newTown;
    string newProduct;
    double currentPrice;
    double currentQuantity;
    for(int i = 0; i < n; ++i)
    {
        cin >> newTown >> newProduct >> currentPrice >> currentQuantity;

        currentPrice *= currentQuantity;
        myMap[newTown] += currentPrice;
    }

    cout.setf(ios::fixed);
    cout.precision(2);

    for(map<string, double>::iterator it = myMap.begin(); it != myMap.end(); ++it)
    {
        cout << it -> first << " -> " << it -> second << endl;
    }

    return 0;
}


