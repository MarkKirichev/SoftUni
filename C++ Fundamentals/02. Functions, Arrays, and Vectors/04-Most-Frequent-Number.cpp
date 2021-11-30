#include <iostream>
using namespace std;

void readArray(int arr[], int size, int counter[])
{
    for(int i = 0; i < size; ++i)
    {
        cin >> arr[i];
        counter[arr[i]]++;
    }
}

int main()
{
    int size;
    cin >> size;

    const short x = 10;
    int counter[x];
    for(int i = 0; i < x; ++i)
    {
        counter[i] = 0;
    }

    int arr[size];
    readArray(arr, size, counter);

    short max_count = 0;
    for(int i = 0; i < x; ++i)
    {
        if(max_count < counter[i])
        {
            max_count = counter[i];
        }
    }

    for(int i = 0; i < x; ++i)
    {
        if(max_count == counter[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}

