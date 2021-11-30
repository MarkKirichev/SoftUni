#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>

using namespace std;

void fillMyMap (unordered_map <string, int>& myMap, queue<string>& myQueue, string& currentMaterial, int currentValue)
{
    if(myMap.find(currentMaterial) == myMap.end())
    {
        myQueue.emplace(currentMaterial);
    }
    myMap[currentMaterial] += currentValue;
}

int main()
{
    unordered_map <string, int> myMap;
    queue<string> myQueue;

    const string endOfSequence = "stop";
    string newWord;
    string newValue;
    
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    while(cin >> newWord && newWord != endOfSequence && cin >> newValue)
    {
        if(newWord == endOfSequence)
        {
            break;
        }
        fillMyMap(myMap, myQueue, newWord, stoi(newValue));
    }

    while(!myQueue.empty())
    {
        ///printf("%s -> %d\n", myQueue.front(), myMap[myQueue.front()]);
        cout << myQueue.front() << " -> " << myMap[myQueue.front()] << endl;
        myQueue.pop();
    }
    return 0;
}

