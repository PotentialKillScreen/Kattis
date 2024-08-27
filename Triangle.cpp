#include <bits/stdc++.h>
#include <iostream>


using namespace std;
int main() {

    int nTriangles;
    int x1, y1, x2, y2, x3, y3;
    int v1x,v1y,v2x,v2y,v3x, v3y;
    int scalarProduct_1, scalarProduct_2,scalarProduct_3;
    double length_1,length_2,length_3;
    double lengthProd_1, lengthProd_2, lengthProd_3;
    cin >> nTriangles;

    // Loop indefinitely until input is "exit"
    for (int i = 1; i <= nTriangles; i++){
        cin >> x1;
        cin >> y1;
        cin >> x2;
        cin >> y2;
        cin >> x3;
        cin >> y3;
        
        v1x = x2-x1;
        v1y = y2-y1;
        v2x = x3-x2;
        v2y = y3-y2;
        v3x = x1-x3;
        v3y = y1-y3;

        scalarProduct_1 = v1x*v2x + v1y*v2y;
        scalarProduct_2 = v2x*v3x + v2y*v3y;
        scalarProduct_3 = v3x*v1x + v3y*v1y;

        length_1 = sqrt(v1x*v1x + v1y*v1y);
        length_2 = sqrt(v2x*v2x + v2y*v2y);
        length_3 = sqrt(v3x*v3x + v3y*v3y);
        //cout << length_1 << " " << length_2 << " " << length_3 << " " << endl;

        //cout << scalarProduct_1<< " " << scalarProduct_2<< " " << scalarProduct_3<< " " << endl;

        lengthProd_1 = length_1*length_2;
        lengthProd_2 = length_2*length_3;
        lengthProd_3 = length_3*length_1;



        cout << "Case #" << i << ": ";

        if ((x1 == x2 && y1 == y2) || (x2 == x3 && y2 == y3) || (x3 == x1 && y3 == y1)) {
            cout << "not a triangle" << endl;
            continue;
        }

        if (v1x * (y3 - y1) - (x3 - x1) * v1y == 0) {
            cout << "not a triangle" << endl;
            continue;
        }
        if (scalarProduct_1 == lengthProd_1 || scalarProduct_2 == lengthProd_2 || scalarProduct_3 == lengthProd_3){
            cout << "not a triangle" << endl;
            continue;
        }
        if (length_1 == length_2 || length_2 == length_3 || length_3 == length_1) {
            cout << "isosceles "; 
        } else {
            cout << "scalene ";
        }
        if (scalarProduct_1 == 0 || scalarProduct_2 == 0 || scalarProduct_3 == 0){
            cout << "right ";
        } else if (scalarProduct_1 > 0 || scalarProduct_2 > 0 || scalarProduct_3 > 0){
            cout << "obtuse ";
        }
        else {
            cout << "acute ";
        }
        cout << "triangle" << endl;



    }
    return 0;
}              