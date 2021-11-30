#include <iostream>
using namespace std;

bool areEqual(int arr1[], int size1, int arr2[], int size2)
{
    if(size1 != size2)
    {
        return false;
    }
    else
    {
        for(int i = 0; i < size1; ++i)
        {
            if(arr1[i] != arr2[i])
            {
                return false;
            }
        }
        return true;
    }
}

void readArray(int arr[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        cin >> arr[i];
    }
}

int main()
{
    int n, m;

    cin >> n;
    int arr1[n];
    readArray(arr1, n);

    cin >> m;
    int arr2[m];
    readArray(arr2, m);

    if(areEqual(arr1, n, arr2, m))
    {
        cout << "equal" << endl;
    }
    else
    {
        cout << "not equal" << endl;
    }
    return 0;
}

