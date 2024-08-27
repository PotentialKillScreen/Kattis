#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

using namespace std;

struct Point {
    double x, y;
};

double distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double pointToLineDistance(const Point& p, const Point& a, const Point& b) {
    double abx = b.x -a.x;
    double aby = b.y - a.y;
    double apx = p.x - a.x;
    double apy = p.y -a.y;

    double ab_ab = abx * abx + aby * aby; 
    double ap_ab = apx * abx + apy * aby; 
    double t = ap_ab / ab_ab;

    if (t < 0.0) t = 0.0;
    else if (t > 1.0) t = 1.0;

    Point nearest;
    nearest.x = a.x + t * abx;
    nearest.y = a.y + t * aby;

    return distance(p, nearest);
}

double findMinDistance(const vector<Point>& inner, const vector<Point>& outer) {
    double minDist = numeric_limits<double>::max();

    for (const auto& p : inner) {
        for (size_t i = 0; i < outer.size(); ++i) {
            const auto& a = outer[i];
            const auto& b = outer[(i + 1) % outer.size()]; 

            double d = pointToLineDistance(p, a, b);
            if (d < minDist) {
                minDist = d;
            }
        }
    }

    return minDist;
}

int main() {
    int nCases;
    cin >> nCases;

    for (int i = 0; i < nCases; i++) {
        int nInner;
        cin >> nInner;
        vector<Point> inner(nInner);

        for (int j = 0; j < nInner; j++) {
            cin >> inner[j].x >> inner[j].y;
        }

        int nOuter;
        cin >> nOuter;
        vector<Point> outer(nOuter);

        for (int j = 0; j < nOuter; j++) {
            cin >> outer[j].x >> outer[j].y;
        }

        double minDist = findMinDistance(inner, outer)/2;
        cout.precision(8);
        cout << fixed << minDist << endl;
    }

    return 0;
}
