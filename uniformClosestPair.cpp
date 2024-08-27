// Author: Axel Ahlqvist
// Problem: Point Sets - Closest Pair of Points - Average Case
// The objective is to find the two closest points in a set of points.
// Algorithm: Divide and Conquer
// Time complexity: O(n log n) where n is the number of points.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <limits>
#include <stdexcept>

using namespace std;

struct Point {
    double x, y;
    int index; // Original index
    // Overload the equality operator to compare points with a tolerance for floating-point precision.
    bool operator==(const Point& other) const {
        return fabs(x - other.x) < 1e-9 && fabs(y - other.y) < 1e-9;
    }
};

struct PointPair {
    int i, j;
    double dist;

};

// Function to read the input and store it in a vector of strings
vector<string> getInput() {
    vector<string> input;
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
        if (line == "0") break;
    }
    return input;
}

// Function to parse the input strings and convert them into a vector of points
vector<vector<Point>> parseInput(const vector<string>& input) {
    vector<vector<Point>> testCases;
    vector<Point> points;
    int n = 0;
    for (const auto& line : input) {
        if (line == "0") {
            if (!points.empty()) testCases.push_back(points);
            break;
        }
        istringstream iss(line);
        if (n == 0) {
            iss >> n;
            if (n <= 0 || n > 100000) throw runtime_error("Invalid number of points.");
            points.reserve(n);
        } else {
            
            Point p;
            iss >> p.x >> p.y;
            if (iss.fail()) throw runtime_error("Invalid point format.");
            p.index = points.size(); // Save the original index
            points.push_back(p);
            n--;
            if (n == 0) {
                testCases.push_back(points);
                points.clear();
            }
            
        }
    }
    return testCases;
}

// Function to calculate the Euclidean distance between two points
double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


// Helper function to find the closest pair of points in a strip
PointPair stripClosest(const vector<Point>& strip, double d, PointPair bestPair) {
    double minDist = d;
    // Compare each point with the next points within the strip
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            double dist = distance(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
                bestPair.dist = dist;
                bestPair.i = strip[i].index;
                bestPair.j = strip[j].index;
            }
        }
    }
    return bestPair; // Return the best pair found in the strip
}

// Helper function to find the closest pair of points using divide and conquer
// The function recursively divides the set of points and combines the results.
PointPair closestPairUtil(const vector<Point>& Px, const vector<Point>& Py) {
    // Initialize a PointPair object to store the closest pair of points.
    PointPair closestPair;
    closestPair.i = -1;
    closestPair.j = -1;
    closestPair.dist = numeric_limits<double>::max();
    // Base case: if the set has 3 or fewer points, solve by brute force
    if (Px.size() <= 3) {
        double minDist = numeric_limits<double>::max();
        PointPair bestPair;
        for (size_t i = 0; i < Px.size(); ++i) {
            for (size_t j = i + 1; j < Px.size(); ++j) {
                if (Px[i] == Px[j]) {
                    bestPair.i = Px[i].index;
                    bestPair.j = Px[j].index;
                    bestPair.dist = 0.0;
                    return bestPair;
                }
                double dist = distance(Px[i], Px[j]);
                if (dist < minDist) {
                    minDist = dist;
                    bestPair.i = Px[i].index;
                    bestPair.j = Px[j].index;
                    bestPair.dist = dist;
                }
            }
        }
        return bestPair;
    }

    // Find the midpoint and divide the set into two halves
    size_t mid = Px.size() / 2;
    Point midPoint = Px[mid];

    // Split points into left and right subsets based on the midpoint
    vector<Point> Pyl, Pyr;
    Pyl.reserve(mid);
    Pyr.reserve(Px.size() - mid);
    for (const auto& p : Py) {
        if (p.x <= midPoint.x && Pyl.size() < mid) {
            Pyl.push_back(p);
        } else {
            Pyr.push_back(p);
        }
    }

    // Recursively find the closest pairs in the left and right halves
    PointPair dl = closestPairUtil(vector<Point>(Px.begin(), Px.begin() + mid), Pyl);
    PointPair dr = closestPairUtil(vector<Point>(Px.begin() + mid, Px.end()), Pyr);
    double d = min(dl.dist, dr.dist);
    PointPair bestPair = dl.dist <= dr.dist ? dl : dr;

    // Build a strip that includes points within distance d of the midpoint
    vector<Point> strip;
    for (const auto& p : Py) {
        if (fabs(p.x - midPoint.x) < d) {
            strip.push_back(p);
        }
    }

    // Find the closest pair in the strip and return the overall best pair
    return stripClosest(strip, d, bestPair);
}

// Function to find the closest pair of points and return their indexes
pair<int, int> closest_pair(vector<Point>& points) {
    if (points.size() < 2) throw runtime_error("Not enough points to form a pair.");
    vector<Point> Px = points;
    vector<Point> Py = points;
    sort(Px.begin(), Px.end(), [](const Point& a, const Point& b) { return a.x < b.x; });
    sort(Py.begin(), Py.end(), [](const Point& a, const Point& b) { return a.y < b.y; });
    PointPair bestPair = closestPairUtil(Px, Py);
    return {bestPair.i, bestPair.j};
}

// Function to print the output in the desired format
void printOutput(const pair<int, int>& indexes, const vector<Point>& points) {
    const Point& p1 = points[indexes.first];
    const Point& p2 = points[indexes.second];
    cout << fixed << setprecision(2) << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << endl;
}

vector<string> testCase1 = {
    "2",
    "1.12 0",
    "0 0.51",
    "3",
    "158 12",
    "123 15",
    "1859 -1489",
    "3",
    "21.12 -884.2",
    "18.18 43.34",
    "21.12 -884.2",
    "0"
};


vector<string> testCase2 = {
    "2",
    "1.0 1.0",
    "2.0 2.0",
    "0"
};

vector<string> testCase3 = {
    "3",
    "1.0 1.0",
    "2.0 2.0",
    "1.5 1.5",
    "0"
};

vector<string> testCase4 = {
    "3",
    "1.0 1.0",
    "2.0 2.0",
    "1.0 1.0",
    "0"
};

vector<string> testCase5 = {
    "2",
    "100000.0 100000.0",
    "-100000.0 -100000.0",
    "0"
};

vector<string> testCase6 = {
    "5",
    "3.2 4.5",
    "-2.1 -1.4",
    "5.6 7.8",
    "0.0 0.0",
    "-5.6 -7.8",
    "0"
};

vector<string> testCase7 = {
    "4",
    "1.0 1.0",
    "2.0 2.0",
    "3.0 3.0",
    "4.0 4.0",
    "0"
};


vector<string> testCase8 = {
    "10",
    "10.0 10.0",
    "20.0 20.0",
    "30.0 30.0",
    "40.0 40.0",
    "50.0 50.0",
    "60.0 60.0",
    "70.0 70.0",
    "80.0 80.0",
    "90.0 90.0",
    "100.0 100.0",
    "0"
};

vector<string> testCase9 = {
    "3",
    "-1.0 -1.0",
    "-2.0 -2.0",
    "-1.5 -1.5",
    "0"
};

vector<string> testCase10 = {
    "9",
    "1.0 1.0",
    "1.0 2.0",
    "1.0 3.0",
    "2.0 1.0",
    "2.0 2.0",
    "2.0 3.0",
    "3.0 1.0",
    "3.0 2.0",
    "3.0 3.0",
    "0"
};

vector<string> testCase11 = {
    "4",
    "100000.0 100000.0",
    "100000.01 100000.02",
    "-100000.02 100000.02",
    "99999.99 99999.99",
    "0"
};

vector<string> testCase12 = {
    "9",
    "1.01 1.01",
    "1.01 2.0",
    "1.01 -3.52",
    "1.01 -2.31",
    "5.0 -2.31",
    "3.5 -2.31",
    "3.0 -2.31",
    "4.0 -2.0",
    "3.0 3.0",
    "0"
};
//3.50 -2.31 3.00 -2.31

vector<string> testCase13 = {
    "9",
    "1.01 1.01",
    "1.01 2.0",
    "1.01 -3.52",
    "1.01 -2.31",
    "5.0 -2.31",
    "3.5 -2.31",
    "-3.0 -2.31",
    "4.0 -2.0",
    "3.0 3.0",
    "0"
};
//3.50 -2.31 4.00 -2.00

vector<string> testCase14 = {
    "11",
    "1.01 1.01",
    "1.01 2.0",
    "1.01 -3.52",
    "1.01 -2.31",
    "5.0 -2.31",
    "3.5 -2.31",
    "-3.0 -2.31",
    "-5.0 -2.31",
    "3.0 3.0",
    "51 -2.31",
    "1.09 -2.91"
    "9",
    "1.01 1.01",
    "1.01 2.0",
    "1.01 -3.52",
    "1.01 -2.31",
    "5.0 -2.31",
    "3.5 -2.31",
    "-3.0 -2.31",
    "4.0 -2.0",
    "3.0 3.0",
    "0"
};
//1.01 -3.52 1.09 -2.92
//3.50 -2.31 4.00 -2.00

vector<string> testCase15 = {
    "11",
    "1.01 1.01",
    "1.01 2.0",
    "1.01 -3.52",
    "1.01 -2.31",
    "5.0 -2.31",
    "3.5 -2.31",
    "-3.0 -2.31",
    "-5.0 -2.31",
    "3.0 3.0",
    "51 -2.31",
    "1.09 -2.92"
    "0"
};
//1.01 -3.52 1.09 -2.92

    /*
    //Test to run the code with a testcase of 100k points followed by another testCase.

    vector<string> testCase17;
    testCase17.push_back("100000");

    for (int i = 0; i < 100000; i++) {
        double x = static_cast<double>(i) / 100.0;
        double y = static_cast<double>(i) / 100.0;
        stringstream ss;
        ss << fixed << setprecision(2) << x << " " << y;
        testCase17.push_back(ss.str());
    }
    for (int i = 0; i < 12; i++) {
        testCase17.push_back(testCase15[i]);
    }
    testCase17.push_back("0");
    for (int i = 0; i < 10014; i++) {
        cout << testCase17[i] << endl;
    }
*/

//Main function to read input, process each test case, and print the results.
//A divide and conquer algorithm is used to find the closest pair of points.
int main() {
    vector<string> input = getInput();
    //vector<string> input = testCase14;
    
    try {
        auto testCases = parseInput(input);

        for (const auto& points : testCases) {
            if (points.size() < 2) continue;
            auto indexes = closest_pair(const_cast<vector<Point>&>(points));
            printOutput(indexes, points);
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
