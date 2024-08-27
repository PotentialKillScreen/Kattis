//Author: Axel Ahlqvist
//Problem: 3.4 Rational Arithmetic 
//Functionality to handle rational arithmetic from command line inputs
//Algorithm: The Euclidean algorithm. (For finding gcd) 
#include<bits/stdc++.h>


using namespace std;
//Euclidian algorithm for finding the greatest common denominator
long long int gcd(long long int a, long long int b){
    if (b == 0){
        return a;
    }
    return gcd(b, a% b);
}
//Class for storing a rational number using operations on it. 
class Rational{
private:
        long long int numerator, denominator;

public:
//Initializer
        Rational(long long int numerator,long long int denominator){
            this->numerator = numerator;
            this->denominator = denominator;
            this->simplify();
        }
//Method to simplify expression by dividing with gcd
        void simplify(){
            long long int gCD = gcd(numerator,denominator);
            numerator = numerator/gCD;
            denominator = denominator/gCD;
            if (numerator > 0 && denominator < 0){
                numerator = -numerator;
                denominator = -denominator;
            }
        } 
        void printRational(){
//Method for printing the rational number in a readable way
            cout << numerator <<" / " << denominator << endl;
        }
//Overloading of the four arithmetric operators which include simplyfing the expression
        Rational operator+(Rational & other) const{
            Rational rational(this->numerator*other.denominator + other.numerator*this->denominator, this->denominator * other.denominator);
            rational.simplify(); 
            return rational;
        }
        Rational operator-(Rational & other) const{
            Rational rational(this->numerator*other.denominator - other.numerator*this->denominator, this->denominator * other.denominator);
            rational.simplify(); 
            return rational;
        }
        Rational operator*(Rational & other) const{
            Rational rational(this->numerator*other.numerator, this->denominator*other.denominator);
            rational.simplify();
            return rational;
        }
        Rational operator/(Rational & other) const{
            Rational rational(this->numerator*other.denominator, other.numerator*this->denominator);
            rational.simplify(); 
            return rational;
        }
//The six comparison operators
        bool operator<(Rational & other) const{
            bool output = (this->numerator*other.denominator<other.numerator*this->denominator);
            return output;
        }
        bool operator>(Rational & other) const{
            bool output = (this->numerator*other.denominator>other.numerator*this->denominator);
            return output;
        }
        bool operator<=(Rational & other) const{
            bool output = (this->numerator*other.denominator<=other.numerator*this->denominator);
            return output;
        }
        bool operator>=(Rational & other) const{
            bool output = (this->numerator*other.denominator>=other.numerator*this->denominator);
            return output;
        }
        bool operator==(Rational & other) const{
            bool output = (this->numerator*other.denominator==other.numerator*this->denominator);
            return output;
        }
        bool operator!=(Rational & other) const{
            bool output = (this->numerator*other.denominator!=other.numerator*this->denominator);
            return output;
        }
};



int main(){
    int nTests;
//input number of test cases
    cin >> nTests; 
    for (int i= 0; i<nTests; i++){
        long long int a,b;
        char op;
        Rational result(1,1);
//Input the nominator, then denominator for the first rational number
        cin >> a;
        cin >> b;
        Rational r1(a,b);
//input the operator
        cin >> op;
//Input the nominator, then denominator for the second rational number
        cin >> a;
        cin >> b;
        Rational r2(a,b);
//Does the operators corresponding operation
        if (op == '+'){
           result = r1+r2;
        }
        if (op == '-'){
           result = r1-r2;
        }
        if (op == '*'){
           result = r1*r2;
        }   
        if (op == '/'){
           result = r1/r2;
        }
//print the output 
        result.printRational(); 
    }
    cout << endl;
    return 0;
}
