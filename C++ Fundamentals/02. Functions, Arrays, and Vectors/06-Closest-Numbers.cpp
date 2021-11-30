#include <iostream>
#include <algorithm>
using namespace std;

void readArray(int arr[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        cin >> arr[i];
    }
}

int main()
{
    int size;
    cin >> size;
    if(size == 1)
    {
        int x;
        cin >> x;
        cout << 0 << endl;
        return 0;
    }

    int arr[size];
    readArray(arr, size);

    sort(arr, arr + size);
    int diff;
    int max_diff = arr[1] - arr[0];
    if(max_diff < 0)
    {
        max_diff = -max_diff;
    }
    for(int i = 2; i < size; ++i)
    {
        diff = arr[i] - arr[i-1];
        if(max_diff < 0)
        {
            diff = -diff;
        }
        if(diff < max_diff)
        {
            max_diff = diff;
        }
    }
    cout << max_diff << endl;

    return 0;
}


