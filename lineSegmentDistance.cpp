// Author: Axel Ahlqvist
// Problem: 4.4 Distance Between Line Segments
// The objective is to find the smallest distance between two line segments.
// Algorithm: Segment intersection and projecting methods
// Time complexity: (1) per segment pair.

#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;


struct Point {
    double x, y;
    bool operator==(const Point& other) const {
        return std::fabs(x - other.x) < 1e-9 && std::fabs(y - other.y) < 1e-9;
    }
};

struct LineSegment {
    Point p1, p2;
};

// Function to read input and store it in a vector of strings
//The first line of input contains the number of test cases n.
//Then follows n test cases, each with 8 integers representing the 
//endpoints coordinates of two line segments.
vector<std::string> getInput() {
    std::vector<std::string> input;
    std::string line;
    int n;
    std::cin >> n;
    input.push_back(std::to_string(n));
    std::cin.ignore();
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        input.push_back(line);
    }
    return input;
}



// Function to check if point q lies on the line segment pr
bool onSegment(Point p, Point q, Point r) {
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}

// Function to find the orientation of the ordered triplet (p, q, r)
// Returns 0 if collinear, 1 if clockwise, and 2 if counterclockwise
int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (std::fabs(val) < 1e-9) return 0; // collinear
    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

// Function to find the intersection of two line segments
//Uses the logic that in if two line intersections intersect,
//the orientation from one line to the two endpoints of the other line
//should be different. Also handles the special cases of colinearity.
std::vector<Point> intersect(LineSegment seg1, LineSegment seg2) {
    Point p1 = seg1.p1, q1 = seg1.p2, p2 = seg2.p1, q2 = seg2.p2;
    std::vector<Point> result;
    
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    
    // General case: segments intersect at a point
    if (o1 != o2 && o3 != o4) {
        double A1 = q1.y - p1.y;
        double B1 = p1.x - q1.x;
        double C1 = A1 * p1.x + B1 * p1.y;
        
        double A2 = q2.y - p2.y;
        double B2 = p2.x - q2.x;
        double C2 = A2 * p2.x + B2 * p2.y;
        
        double det = A1 * B2 - A2 * B1;
        if (std::fabs(det) > 1e-9) {
            double x = (B2 * C1 - B1 * C2) / det;
            double y = (A1 * C2 - A2 * C1) / det;
            result.push_back({x, y});
        }
    }
    
    // Special cases: segments are collinear and may overlap
    if (o1 == 0 && onSegment(p1, p2, q1)) result.push_back(p2);
    if (o2 == 0 && onSegment(p1, q2, q1)) result.push_back(q2);
    if (o3 == 0 && onSegment(p2, p1, q2)) result.push_back(p1);
    if (o4 == 0 && onSegment(p2, q1, q2)) result.push_back(q1);
    
    // Ensure the points are unique and sorted
    if (result.size() > 1) {
        std::sort(result.begin(), result.end(), [](const Point& a, const Point& b) {
            if (a.x == b.x) return a.y < b.y;
            return a.x < b.x;
        });
        result.erase(std::unique(result.begin(), result.end()), result.end());
    }
    
    return result;
}

// Function to convert 8 coordinates into a pair of line segments
vector<pair<LineSegment, LineSegment>> CreateSegments(const vector<vector<double>>& coordinates) {
    vector<pair<LineSegment, LineSegment>> segments;
    for (const auto& coords : coordinates) {
        LineSegment seg1 = { {coords[0], coords[1]}, {coords[2], coords[3]} };
        LineSegment seg2 = { {coords[4], coords[5]}, {coords[6], coords[7]} };
        segments.push_back({ seg1, seg2 });
    }
    return segments;
}

// Function to parse the input strings and convert them into a vector of LineSegments
vector<pair<LineSegment, LineSegment>> parseInput(const vector<string>& input) {
    vector<vector<double>> coordinates;
    for (const auto& line : input) {
        istringstream iss(line);
        vector<double> coords;
        double value;
        while (iss >> value) {
            coords.push_back(value);
        }
        coordinates.push_back(coords);
    }
    return CreateSegments(coordinates);
}



// Helper function to calculate the Euclidean distance between two points
double pointDistance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Function to calculate the smallest distance between two line segments
//If the segments intersect, the distance is 0.00. Otherwise use projection
//to calculate the the four distances between the endpoints and the other 
//segment. Return the smallest of these four distances. 
double segmentDistance(const LineSegment& seg1, const LineSegment& seg2) {

    vector<Point> Intersect = intersect(seg1, seg2);
    if (!Intersect.empty()) {
        return 0.00;
    }
    auto pointToSegmentDistance = [](const Point& p, const LineSegment& seg) -> double {
        auto dot = [](const Point& p1, const Point& p2) -> double {
            return p1.x * p2.x + p1.y * p2.y;
        };
        auto projection = [dot](const Point& p, const Point& p1, const Point& p2) -> Point {
            Point v = { p2.x - p1.x, p2.y - p1.y };
            Point w = { p.x - p1.x, p.y - p1.y };
            double c1 = dot(w, v);
            double c2 = dot(v, v);
            double b = c1 / c2;
            Point Pb = { p1.x + b * v.x, p1.y + b * v.y };
            return Pb;
        };

        Point Pb = projection(p, seg.p1, seg.p2);
        if ((min(seg.p1.x, seg.p2.x) <= Pb.x && Pb.x <= max(seg.p1.x, seg.p2.x)) &&
            (min(seg.p1.y, seg.p2.y) <= Pb.y && Pb.y <= max(seg.p1.y, seg.p2.y))) {
            return pointDistance(p, Pb);
        } else {
            return min(pointDistance(p, seg.p1), pointDistance(p, seg.p2));
        }
    };

    return min({
        pointToSegmentDistance(seg1.p1, seg2),
        pointToSegmentDistance(seg1.p2, seg2),
        pointToSegmentDistance(seg2.p1, seg1),
        pointToSegmentDistance(seg2.p2, seg1)
    });
}

// Function to print the distance in the desired format
void printOutput(double distance) {
    cout << fixed << setprecision(2) << distance << endl;
}

vector<string> testCase1 = {
        "5",
        "-10 0 10 0 0 -10 0 10",
        "-10 0 10 0 -5 0 5 0",
        "1 1 1 1 1 1 2 1",
        "1 1 1 1 2 1 2 1",
        "1871 5789 216 -517 189 -1518 3851 1895"
    };

//Main function that takes the input as a vector of strings,
//parses the input to create a pair of LineSegments for each testcase.
//For each pair of LineSegments, the function calculates the distance.
//Finally the results are printed in the desired format.
//The input coordinates need to be integers.
int main() {
    vector<string> input = getInput();

    int n = stoi(input[0]);
    vector<string> test_cases(input.begin() + 1, input.end());
    auto lineSegments = parseInput(test_cases);
    for (const auto& pair : lineSegments) {
        double distance = segmentDistance(pair.first, pair.second);
        printOutput(distance);
    }

    return 0;
}