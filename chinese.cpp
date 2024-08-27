//Author: Axel Ahlqvist
//Problem: Chinese remained theorem 
//Implements arithmetic modulo n 
//Algorithm: Extended euclidian algorithm
//Time complexity: O(log N)
#include<bits/stdc++.h>

using namespace std;

//Multiply with mod
long long int modMultiply(long long int a, long long int b, long long int n) {
    long long int r;
    bool d;
    if (a == 0 or b == 0) {
        return 0;
    }
    if (b == 1) {
        return a;
    } 
    if (a == 1) {
        return b;
    }
//Using a trick to where the mod is taking multiple times in order to not get overflow problems
    long long int half = modMultiply(a, b / 2, n);
    d = (b % 2);
    r = (d*(a%n) + 2*half)%n;
    return r;
}


//extended euclidean algorithm which in addition to gcd also calculates the coefficients of the Bezouts identity
void exeuclid(long long int a, long long int b, long long int *x,long long int *y){
    if (!b) {
        *x = 1;
        *y = 0;
    }
    else {
        exeuclid(b, a%b, y,x);
        *y -= *x *(a/b);
    }
}


//Finds the modular inverse to b
//returns -1 if b and n is congruent as that behaviour is not defined for 
//modular division
long long int inv(long long int b,long long int n){
    long long int x, y; 
    exeuclid(b,n, &x, &y);
    return (x%n + n) % n;
}
 
//The result from mod dividing a with b = r. Such that (r * b)%n = a
//returns -1 if there is no such r
long long int modDivide(long long int a,long long int b,long long int n){
    long long int result;
    long long int inverse = inv(b, n);
    a = a % n;
    result = modMultiply(inverse,a,n);
    return result;
}
 
//Using modular arithmetic to solve the equation 
long long int chinese(long long int a, long long int n, long long int b, long long int m){
    long long int m1,m2,M1,M2,M,y1,y2,r,r1,r2;
    M = n * m;
    M1 = M/n;
    M2 = M/m;
    y1 = modDivide(1,M1,n);
    y2 = modDivide(1,M2,m);
    r1 = modMultiply(a,M1*y1,M);
    r2 = modMultiply(b,M2*y2,M); 
    r = (r1 + r2)%M;
    return r;
}


int main(){
    int nTests;
//Input the number of testcases
    cin >> nTests;
    long long int result;
    for (int i = 0; i<nTests; i++){
        long long int a,n,b,m;
//Input in the following order: a, n, b and m.
        cin >> a;
        cin >> n;
        cin >> b;
        cin >> m;
//Solving the equation x = a(mod n), x = b(mod m).
        result = chinese(a,n,b,m);
//Prints the results
        cout << result << " " << m*n << endl;
    }
    cout << endl;
    return 0;
} 
