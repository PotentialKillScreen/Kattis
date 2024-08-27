// Author: Axel Ahlqvist
// Problem: Intersection of Line Segments
// The objective is to find the point or line that intersects two line segments.
// Algorithm: Orientation and segment intersection
// Time complexity: O(1) per segment pair check, O(n) for processing n pairs

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

// Structure to represent a point with x and y coordinates
struct Point {
    double x;
    double y;
    
    // Equality operator to compare two points with precision tolerance
    bool operator==(const Point& other) const {
        return std::fabs(x - other.x) < 1e-9 && std::fabs(y - other.y) < 1e-9;
    }
};

// Structure to represent a line segment defined by two points
struct LineSegment {
    Point p1;
    Point p2;
};

// Function to read input and store it in a vector of strings
//The first line of input contains the number of test cases n.
//Then follows n test cases, each with 8 integers representing the 
//endpoints coordinates of two line segments.
std::vector<std::string> getInput() {
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

// Function to parse the input strings and convert them into a vector of LineSegments
std::vector<std::pair<LineSegment,LineSegment>> parseInput(const std::vector<std::string>& input) {
    std::vector<std::pair<LineSegment,LineSegment>> segments;
    int n = std::stoi(input[0]);
    for (int i = 1; i <= n; ++i) {
        LineSegment seg1, seg2;
        sscanf(input[i].c_str(), "%lf %lf %lf %lf %lf %lf %lf %lf",
               &seg1.p1.x, &seg1.p1.y, &seg1.p2.x, &seg1.p2.y, 
               &seg2.p1.x, &seg2.p1.y, &seg2.p2.x, &seg2.p2.y);
        segments.push_back(std::make_pair(seg1,seg2));
    }
    return segments;
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

// Function to print a double value formatted to 2 decimal places
void printFormatted(double value) {
    if (std::fabs(value) < 1e-9) {
        std::cout << "0.00";
    } else {
        std::cout << std::fixed << std::setprecision(2) << value;
    }
}

// Function to print the output for all intersection results
void printOutput(const std::vector<std::vector<Point>>& results) {
    for (const auto& result : results) {
        if (result.empty()) {
            std::cout << "none" << std::endl;
        } else if (result.size() == 1) {
            printFormatted(result[0].x);
            std::cout << " ";
            printFormatted(result[0].y);
            std::cout << std::endl;
        } else if (result.size() == 2) {
            std::vector<Point> orderedResult;
            if (result[0].x < result[1].x || (result[0].x == result[1].x && result[0].y < result[1].y)) {
                orderedResult = {result[0], result[1]};
            }
            else {
                orderedResult = {result[1], result[0]};
            }
            printFormatted(orderedResult[0].x);
            std::cout << " ";
            printFormatted(orderedResult[0].y);
            std::cout << " ";
            printFormatted(orderedResult[1].x);
            std::cout << " ";
            printFormatted(orderedResult[1].y);
            std::cout << std::endl;
        }
    }
}

//Main function that takes the input as a vector of strings,
//parses the input to create a pair of LineSegments for each testcase.
//For each pair of LineSegments, the function calculates the intersection
//point or line and saves the result in a vector.
//Finally the results are printed in the desired format.
//The input coordinates need to be integers.
//In case no intersection is found, the output is "none".
//In case of a line of intersection the lines endpoints are printed.
int main() {
    std::vector<std::string> input = getInput();
    std::vector<std::pair<LineSegment,LineSegment>> segments = parseInput(input);
    
    std::vector<std::vector<Point>> results;
    for (size_t i = 0; i < segments.size(); i++) {
        results.push_back(intersect(segments[i].first, segments[i].second));
    }
    
    printOutput(results);
    return 0;
}
