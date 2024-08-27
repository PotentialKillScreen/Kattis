//Author: Axel Ahlqvist
//Problem: 4.7 Convex Hull
//Given a set of points, the program calculates the points on the convex hull.
//Algorithm: Graham's Scan
//Time complexity: O(NLogN) where N is the number of points.
#include<bits/stdc++.h>
using namespace std;


//Class which represents a 2 dimensional point
template <typename T>
class Point{
public:
    T x, y;
    Point(T a,T b);
};
template <typename T>
//Constructor initializing the coordinates
Point<T>::Point(T a, T b) {
    x = a;
    y = b;
}
        
double polygon_area(vector<Point<int>> points){
//Function that calculates the area.
//The area is positive if the points are in counter clockwise order and 
//negative if the points are in clockwise order
    double sum = 0;
    double tmp= 0;
    int nPoints = points.size();
    for(int i = 0; i < nPoints-1; i++){
        tmp = (double)(points[i+1].y - points[i].y) 
            *(points[i+1].x +points[i].x);
        sum += tmp; 
    } 
    tmp = (double)(points[0].x  + points[nPoints- 1].x)
        *(points[0].y - points[nPoints -1].y); 

    sum += tmp; 
    sum = sum/2;
    return sum;
}

//Struct to enable sorting of points indexes based on angle and distance to the
//first point.
struct sortStruct
{
    long double angle;
    long double dist;
    int index;
};


//Compare function to enable sorting of points based on angle to first point.
//If angle is the same then lower distance to the points is first.
int cmp(const void *a, const void *b)
{
    struct sortStruct *a1 = (struct sortStruct *)a;
    struct sortStruct *a2 = (struct sortStruct *)b;
    if ((*a1).angle< (*a2).angle)
        return -1;
    else if ((*a1).angle > (*a2).angle)
        return 1;
    else if ((*a1).dist <= (*a2).dist)
        return -1;
    else
        return 1;
}

//Function to get the second highest element in a stack without changing the 
//stack
int below_top(stack<int> &stck) {
    int top = stck.top();
    stck.pop();
    int belowTop = stck.top();
    stck.push(top);
    return belowTop;
}

//Function that takes a starting point and a set of points and returns a vector
//of the indexes of the points that creates a simple Polygon 
vector<int> simple_polygon(int start_index, vector<Point<int>> points){
    vector<int> indexes;
    int nPoints = points.size();
    struct sortStruct objects[nPoints];
    for (int i =0; i < nPoints; i++){
        objects[i].index = i;
        if (i ==start_index){
            objects[i].angle = -2*M_PI - 1; 
            objects[i].dist = 0;
            continue;
        }
        long double angle = atan2(points[i].y - points[start_index].y
                ,points[i].x- points[start_index].x);
        long double dist = sqrt(pow(points[i].x - points[start_index].x,2) 
                +pow(points[i].y - points[start_index].y,2));
        objects[i].angle = angle;
        objects[i].dist = dist; 
    }
    qsort(objects, nPoints, sizeof(objects[0]), cmp); 
    long double prevAngle = objects[0].angle; 
    long double prevDist = 0;
    long double angle;
    long double dist;
    int i =0;
    int removed = 0;
    vector<bool> include(nPoints, true);
    for (int i=0; i<nPoints-removed; i++)
    {
        if (include[i]){
            indexes.push_back(objects[i].index);
        }
    }
    return indexes; 
}

//Function to delete indentical copies of points from a vector.
vector<int> delete_copies(vector<Point<int>> points, vector<int> simplePolygon){
    int index =0;
    while (true){
        int nInHull = simplePolygon.size();
        if (index == nInHull-1){
            break;
        }
        int idx0 = simplePolygon[index];
        int idx1 = simplePolygon[index+1];
        if ((points[idx0].x == points[idx1].x) 
                && (points[idx0].y == points[idx1].y)){
            simplePolygon.erase(simplePolygon.begin()+index+1);
        }
        else {
            index++;
        }
    } 
    return simplePolygon;
}

//Main Function. Takes a vector of points and returns a vector of 
//indexes of the points that make up the convex hull.
vector<int> convex_hull(vector<Point<int>> points){
    vector<int> indexes{};
    int nPoints = points.size();
    int min = INT_MAX;
    int xMin = INT_MAX;
    int min_index;
    vector<bool> inHull(nPoints,1);
//Finds the point with lowest y-coordinate. 
//If multiple takes the one with smaller x value.
    for (int i = 0; i< nPoints; i++){
        if ((points[i].y < min) || (points[i].y == min && points[i].x < xMin)){
            min = points[i].y;
            xMin = points[i].x;
            min_index = i;
        }
    }
    vector<int> simplePolygon;
//Finds an order of the points that creates a simple polygon. 
    simplePolygon = simple_polygon(min_index, points);
    int counter = 0;
    bool entireLap = false;

    int nSimple = simplePolygon.size();
    stack<int> hull;
    hull.push(simplePolygon[0]);
    if (nSimple >1){
        hull.push(simplePolygon[1]);
    }
    if (nSimple > 2){
        //includes points in the stack when they create a counter clockwise
        //turn. Removoes previous points until that is possible. 
        for (int i =2; i<nSimple; i++){
            while (hull.size()>1 
                    && polygon_area({points[below_top(hull)], 
                        points[hull.top()], points[simplePolygon[i]]}) <=0){
                hull.pop();
            }
            hull.push(simplePolygon[i]);
        } 
    }
    int hullSize = hull.size();
    vector<int> output(hullSize,100);
    for (int i = 0;i<hullSize; i++){ 
        output[hullSize-1-i] = hull.top();
        hull.pop();
    }
   //delete copies before returning 
    return delete_copies(points,output);
}




int main(){
    while(true){
        int nPoints;
//Input number of points
        scanf("%d", &nPoints);
        if (nPoints == 0){
            break;
        }
        int x,y;
        vector<Point<int>> points; 
//Input coordinate x and then coordinate y for each point
        for (int i = 0; i < nPoints; i++){
            scanf("%d %d", &x,&y);
            Point<int> point(x,y);
            points.push_back(point);
        }
        stack<int> indexStack;   
        vector<int> output;
        output = convex_hull(points);     
        int nHullPoints = output.size();
//Outputs the number of points in the convex hull
        printf("%d\n", nHullPoints);
//For each point in the hull prints the x and then the y coordinate
        for (int i =0; i< nHullPoints; i++){
            int index = output[i];
            printf("%d %d\n", points[index].x, points[index].y);
        }
    }
    return 0;
}

