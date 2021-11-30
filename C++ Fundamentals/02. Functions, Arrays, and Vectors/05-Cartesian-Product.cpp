#include <iostream>
using namespace std;

void readArray(int arr[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        cin >> arr[i];
    }
}

void showCartesians(int arr[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            cout << arr[i] * arr[j] << " ";
        }
    }
    cout << endl;
}

int main()
{
    int size;
    cin >> size;

    int arr[size];
    readArray(arr, size);

    showCartesians(arr, size);
    return 0;
}

