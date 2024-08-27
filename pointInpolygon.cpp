//Author: Axel Ahlqvist
//Problem: Point in Polygon 
//Calculates wheter a point is inside, outside or on the edge the polygon
//Time complexity: O(N). N = Number of points in polygon.
#include<bits/stdc++.h>

using namespace std;


template <typename T>
class Point{
    //Class which represents a 2 dimensional vector
public:
    //vector<pair<T,T>> vec; 
    T x, y;
    Point(T a,T b);
    //T* ptr;
};
template <typename T>
Point<T>::Point(T a, T b) {
    x = a;
    y = b;
}
//takes a vector of points repressenting a polygon and an additional test point as input
//returns an integer repressenting whether the test point is inside (1) on the edge (0) or outside (1) 
//the polygon. It counts the number of crossings if go up in a straight line from the test point. 
int inside_poly(Point<int> point, vector<Point<int>> poly){
    int N = poly.size();
    int slopePart1, slopePart2;
    int crossings = 0;
    int crossBelow = 0;
    int nextStep;
    bool cond1, cond2, above, onLine;
    long double slope;
    bool below = false;
    onLine = false;
//goes through one point at the time on the polygon. The edge between this point and the 
//following point is examined to see wheter the test point is on that edge or if the edge is 
//directly above the test point.
    for (int i = 0; i< N; i++){
        onLine = false;
        nextStep = i+1; 
        if (nextStep == N){
            nextStep = 0;
        }
//Cond1 and cond2 says wether the test points x coordinate is between two points in the
//polygon. Cond1 is when the next point of the polygon has a bigger x coordinate than the last. 
//Cond2 is when the next point has a lower x coordinate than the last point. 
        cond1 = ((poly[i].x <= point.x) && (point.x < poly[nextStep].x));
        cond2 = ((poly[nextStep].x <= point.x) && (point.x < poly[i].x));
        slope = (long double)(poly[nextStep].y - poly[i].y)/(long double)(poly[nextStep].x - poly[i].x);
//If x and y coordinate of point correspond to a point on polygon then it is on the polygon.
        if (point.x == poly[i].x && point.y == poly[i].y){
            return 0;
        }
//Calculates the slope for both the x and the y axis. This is used to calculate whether point is
//on the line.
        slopePart1 = poly[nextStep].y - poly[i].y;
        slopePart2 = poly[nextStep].x - poly[i].x;
        if (slopePart2 == 0 && point.x==poly[i].x){
            if ((point.y <= poly[nextStep].y && poly[i].y <= point.y ) || (point.y <= poly[i].y && poly[nextStep].y <= point.y)){
                return 0; 
            }
        }
        if (slopePart1 == 0 && point.y == poly[i].y){
            if ((point.x <= poly[nextStep].x && poly[i].x <= point.x ) || (point.x <= poly[i].x && poly[nextStep].x <= point.x)) {
               return 0; 
            }
        }
        if (point.y*slopePart2 == slopePart1 * (point.x - poly[i].x) +poly[i].y * slopePart2){
            onLine = true;
        }
        above = (point.y < slope * (point.x - poly[i].x) + poly[i].y);

        if ((cond1 || cond2)&& onLine){
            return 0;
        }
        if ((cond1 || cond2) && above){
            crossings++;
        }
    }
    if (crossings % 2 == 0){
        return -1;
    }
    return 1;
    
}
    
//Uses the integer to print out the corresponding state of the point
void print_output(int results){
    if (results == -1){
        cout << "out" << endl;
    }
    else if (results == 0){
        cout << "on" << endl;
    }
    else if (results == 1){
        cout << "in" << endl;
    }
}
int main(){
    int nPoints,a, b, results, nTests;
    vector<Point<int>> poly;
    vector<Point<int>> tests;
    //double area;
    string turnDirection;
    while (true){
        poly.clear(); 
//Input number of points in polygon
        cin >> nPoints;
        if (nPoints == 0){
            break;
        }
        for (int i = 0; i<nPoints ; i++){
//Input the x coordinate and then the y coordinate for a point on the polygon
            cin >> a;
            cin >> b; 
            Point<int> point(a,b);
            poly.push_back(point);
        } 
//Input the number of points which the program will calculate wheter they are inside or not. 
        cin >> nTests;
        for (int i = 0; i < nTests; i++){
//Input the x coordinate and then the y coordinate for at point that will be tested
            cin >> a;
            cin >> b;
            Point<int> p(a,b);
//Calculates for each point wheter it is outside, inside or on the edge of the polygon.
            results = inside_poly(p, poly);        
//Prints the result in a readable form
            print_output(results);
        }
    }
    cout << endl;

    return 0;
}


