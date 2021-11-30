#include <iostream>
#include <string>

using namespace std;

void capitalizeString (string& sentence)
{
    size_t strSize = sentence.size();
    bool flag = true;

    if(sentence[0] >= 'a' && sentence[0] <= 'z')
    {
        sentence[0] -= 32;
    }
    cout << sentence[0];
    flag = false;

    for(size_t i = 1; i < strSize; ++i)
    {
        if(sentence[i] >= 'a' && sentence[i] <= 'z' && ((sentence[i-1] < 'a' || sentence[i-1] > 'z') && (sentence[i-1] < 'A' || sentence[i-1] > 'Z')))
        {
            flag = true;
        }

        if(flag)
        {
            if(sentence[i] >= 'a' && sentence[i] <= 'z')
            {
                sentence[i] -= 32;
            }
            cout << sentence[i];
            flag = false;
            continue;
        }

        cout << sentence[i];

    }
}

int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    
    string s;
    getline(cin, s);

    capitalizeString(s);

    return 0;
}
