//Author: Axel Ahlqvist
//Problem: Polygon area 
//Calculates an the area of a polygon given its points
//Algorithm: 
//Time complexity: O(N)
#include<bits/stdc++.h>
using namespace std;


template <typename T>
class Point{
//Class which represents a 2 dimensional 
public:
    T x, y;
    Point(T a,T b);
};
template <typename T>
//Constructor using the coordinates
Point<T>::Point(T a, T b) {
    x = a;
    y = b;
}

double polygon_area(vector<Point<int>> points){
//Function that calculates the area.
//The area is positive if the points are in counter clockwise order and negative if 
//the points are in clockwise order
    double sum = 0;
    double tmp= 0;
    int nPoints = points.size();
    for(int i = 0; i < nPoints-1; i++){
        tmp = (double)(points[i+1].y - points[i].y) *(points[i+1].x +points[i].x);
        sum += tmp; 
    } 
    tmp = (double)(points[0].x  + points[nPoints- 1].x)*(points[0].y - points[nPoints -1].y); 
    sum += tmp; 
    sum = sum/2;
    return sum;
}
void print_output(double area){
//Prints in which direction the points where given and the area of the polygon
    if (area > 0){
        cout << "CCW " << fixed << setprecision(1)<< area;
    }
    else {
        cout << "CW " << fixed << setprecision(1)<< -area;
    }
    cout << endl;
}

int main (){
    int nPoints,a, b;
    vector<Point<int>> points;
    double area;
    string turnDirection;
    while (true){
        points.clear(); 
//Input number of points
        cin >> nPoints;
        if (nPoints == 0){
            break;
        }
        for (int i = 0; i<nPoints ; i++){
//Input coordinate x and then coordinate y.
            cin >> a;
            cin >> b; 
            Point<int> point(a,b);
            points.push_back(point);
        } 
//Calculates the area as if the points where given in counter clockwise order
        area = polygon_area(points); 
//Outputs the results
        print_output(area);
    }     
    cout << endl;
    return 0;
}
