#include <iostream>

using namespace std;

int main ()
{
    double a, b, c;
    int br = 0;
    cin >> a >> b >> c;
    if (a == 0 || b == 0 || c == 0)
    {
        cout << "+" << endl; return 0;
    }
    if (a < 0.0) br++;
    if (b < 0.0) br++;
    if (c < 0.0) br++;
    if ((br % 2) == 0) cout << "+" << endl;
    else cout << "-" << endl;
    return 0;
}
