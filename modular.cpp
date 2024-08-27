//Author: Axel Ahlqvist
//Problem: Modular arithmetic 
//Implements arithmetic modulo n 
#include<bits/stdc++.h>


using namespace std;

//extended euclidean algorithm which in addition to gcd also calculates the coefficients of the Bezouts identity
void exeuclid(long long int a, long long int b, long long int *x,long long int *y){
    if (b == 0) {
        *x = 1;
        *y = 0;
    }
    else {
        exeuclid(b, a%b, y,x);
        *y -= *x *(a/b);
    }
}
//Function to find the greatest common divisor using the euclidean algorithm
long long int gcd(long long int b, long long int n){
    if (n == 0){
        return b;
    }
    return gcd(n, b% n);
}


//Finds the modular inverse to b
//returns -1 if b and n is congruent as that behaviour is not defined for 
//modular division
long long int inv(long long int b,long long int n){
    long long int x, y; 
    long long int gCD = gcd(b,n);
 
    if (gCD == 1){
        exeuclid(b,n, &x, &y);
        return (x%n + n) % n;
    }
    return -1;
}
 

long long int modDivide(long long int a,long long int b,long long int n){
//The result from mod dividing a with b = r. Such that (r * b)%n = a
//returns -1 if there is no such r
    long long int result;
    long long int inverse = inv(b, n);
    a = a % n;
    if (inverse == -1){
        result = -1;
    }
    else
    {
        result = (inverse * a) % n ;
    }
    return result;
}
 
//main function that identifies the operator and executes the corresponding operation
long long int moduloOp(long long int a, long long int b, char op, long long int n){
    long long int result;
    long long int tmp;
    if (op =='+'){
        result = (a + b)%n;
    }
    if (op =='-'){
        tmp = a-b;
        result = tmp%n;

        if (tmp < 0){
            result = result+n;
        }
    }

    if (op =='*'){
        result =(a*b)%n;
    }
    if (op =='/'){
        result = -1;
        if (gcd(b,n) == 1){
            result = modDivide(a,b,n);     
        }
    } 
    return result;
}


int main(){
    while(true){
        long long int n;
        int nTests;
//Input modulo number and number of tests
        cin >> n;
        cin >> nTests;
        if (n == 0 && nTests == 0){
           cout << endl;
           break; 
        }
        for (int i= 0; i<nTests; i++){
            long long int a, b, result;
    
            char op;
//Input first integer, then the operator and finally the second integer
            cin >> a;
            cin >> op;
            cin >> b;
            result = moduloOp(a,b,op, n);
//Print results
            cout << result;
            cout << endl; 
        }
    }
    return 0;
}
