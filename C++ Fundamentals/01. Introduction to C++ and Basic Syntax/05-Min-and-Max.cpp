#include <iostream>

using namespace std;

int main ()
{
    int n, x, minx, maxx;
    cin >> n >> x;
    minx = x;
    maxx = x;
    n--;
    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        if (minx < x) minx = x;
        if (maxx > x) maxx = x;
    }
    cout << maxx << " " << minx << endl;
}
