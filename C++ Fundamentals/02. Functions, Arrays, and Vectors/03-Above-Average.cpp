#include <iostream>
#include <cmath>
using namespace std;

int avg;

void readArray(int arr[], int size)
{
    int sum = 0;
    for(int i = 0; i < size; ++i)
    {
        cin >> arr[i];
        sum += arr[i];
    }
    avg = floor(sum / ((double)size));
}

void aboveAverage(int arr[], int size, int average)
{
    for(int i = 0; i < size; ++i)
    {
        if(arr[i] >= average)
        {
            cout << arr[i] << " ";
        }
    }
    cout << "\n";
}

int main()
{
    int size;
    cin >> size;

    int arr[size];
    readArray(arr, size);

    aboveAverage(arr, size, avg);
    return 0;
}
