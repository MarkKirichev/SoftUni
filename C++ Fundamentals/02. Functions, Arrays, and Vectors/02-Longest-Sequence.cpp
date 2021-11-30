#include <iostream>
using namespace std;

struct sequence_data
{
    int num;
    int times;
};

void readArray(int arr[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        cin >> arr[i];
    }
}

void printAnswer(sequence_data x)
{
    for (int i = 0; i < x.times - 1; ++i)
    {
        cout << x.num << " ";
    }
    cout << x.num << endl;
}

void longest_sequence(int arr[], int size)
{
    int counter = 1;
    sequence_data data;
    data.times = 1;
    for (int i = 1; i < size; ++i)
    {
        if(arr[i] == arr[i-1])
        {
            counter++;
        }
        else
        {
            if(counter)
            {
                if (counter >= data.times)
                {
                    data.num = arr[i-1];
                    data.times = counter;
                }
            }
            counter = 1;
        }
    }
    if (counter >= data.times)
    {
        data.num = arr[size-1];
        data.times = counter;
    }
    printAnswer(data);
}

int main()
{
    int size;
    cin >> size;

    int arr[size];
    readArray(arr, size);

    longest_sequence(arr, size);
    return 0;
}

