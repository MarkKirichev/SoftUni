#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, c;
    cin >> a >> b >> c;

    double discriminant = b*b - 4*a*c;
    if (discriminant < 0.0)
    {
        cout << "no roots" << endl;
        return 0;
    }
    else if (discriminant == 0.0)
    {
        b = -b;
        b /= 2.0;
        b /= a;
        cout << b << endl;
    }
    else
    {
        b = -b;
        double x1, x2;
        discriminant = sqrt(discriminant);
        x1 = b + discriminant;
        x2 = b - discriminant;
        x1 /= 2.0;
        x2 /= 2.0;
        x1 /= a;
        x2 /= a;

        cout << x1 << " " << x2 << endl;
        return 0;
    }
}
