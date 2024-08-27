// Author: Axel Ahlqvist
// Problem: 4.8 Point Sets - Maximal Set of Colinear Points
// The objective is to find the largest set of points that are colinear.
// Algorithm: Using slope calculations to determine colinearity.
// Time complexity: O(n^2 log n) where n is the number of points.

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <sstream>

using namespace std;

// Structure to represent a point with x and y coordinates
struct Point {
    int x, y;
};

// Function to read input and store it in a vector of strings. The input can consist
//of multiple test cases following each other. Each test case starts with the number 
// of poitns n, followed by n lines with the integer coordinates for each points.  
vector<string> readInput() {
    vector<string> inputLines;
    string line;
    while (getline(cin, line) && line != "0") {
        inputLines.push_back(line);
    }
    return inputLines;
}

// Function to parse the input strings and convert them into a vector of test cases
// Each test case is a vector of points
vector<vector<Point>> parseInput(const vector<string>& inputLines) {
    vector<vector<Point>> testCases;
    vector<Point> currentCase;
    int index = 0;
    while (index < inputLines.size()) {
        istringstream iss(inputLines[index]);
        int n;
        iss >> n;
        if (n == 0) break;
        currentCase.clear();
        for (int i = 0; i < n; ++i) {
            ++index;
            istringstream pointStream(inputLines[index]);
            int x, y;
            pointStream >> x >> y;
            currentCase.push_back({x, y});
        }
        testCases.push_back(currentCase);
        ++index;
    }
    return testCases;
}

// Greatest common divisor of two integers
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to calculate the normalized slope between two points
pair<int, int> getNormalizedSlope(const Point& a, const Point& b) {
    int dy = b.y - a.y;
    int dx = b.x - a.x;
    if (dx == 0) return {1, 0}; // Vertical line
    if (dy == 0) return {0, 1}; // Horizontal line
    int g = gcd(abs(dy), abs(dx));
    dy /= g;
    dx /= g;
    if (dx < 0) {
        dy = -dy;
        dx = -dx;
    }
    return {dy, dx};
}

// Function that takes a vector of points and returns the number of 
// maxium collinear points in the vector. Uses normalized slope.
int numberOfCollinear(const vector<Point>& points) {
    int n = points.size();
    if (n < 2) return n;
    int maxPoints = 1;
    for (int i = 0; i < n; ++i) {
        map<pair<int, int>, int> slopeCount;
        int duplicate = 1; // Count the point itself
        int vertical = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (points[i].x == points[j].x && points[i].y == points[j].y) {
                duplicate++;
            } else {
                pair<int, int> slope = getNormalizedSlope(points[i], points[j]);
                slopeCount[slope]++;
                vertical = max(vertical, slopeCount[slope]);
            }
        }
        maxPoints = max(maxPoints, vertical + duplicate);
    }
    return maxPoints;
}

// Function to print the results for all test cases
void printResults(const vector<int>& results) {
    for (int result : results) {
        cout << result << endl;
    }
}

// Main function to read input, process each test case, and print the results.
//The coordinates of the input must be integers.
int main() {
    vector<string> inputLines = readInput(); // Read the input lines
    vector<vector<Point>> testCases = parseInput(inputLines); // Parse the input into test cases
    vector<int> results;
    
    // Calculate the maximum number of collinear points for each test case
    for (const vector<Point>& testCase : testCases) {
        results.push_back(numberOfCollinear(testCase));
    }
    
    // Print the results
    printResults(results);
    return 0;
}