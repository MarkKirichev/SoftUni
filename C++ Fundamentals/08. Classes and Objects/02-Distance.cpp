#include <iostream>
#include <cmath>

using namespace std;

class Point
{
    public:
        double firstCoord;
        double secondCoord;

    Point(double firstCoord, double secondCoord)
    {
        this -> firstCoord = firstCoord;
        this -> secondCoord = secondCoord;
    }

    void distanceBetweenPoints (Point y)
    {
        cout.setf(ios::fixed);
        cout.precision(3);

        double distance;
        distance = pow (((this -> firstCoord) - y.firstCoord), 2) + pow(((this -> secondCoord) - y.secondCoord), 2);
        distance = sqrt(distance);

        cout << distance << endl;
    }
};

int main()
{
    double x1, x2;
    double y1, y2;

    cin >> x1 >> x2;
    cin >> y1 >> y2;

    Point x (x1, x2);
    Point y (y1, y2);

    x.distanceBetweenPoints(y);

    return 0;
}
