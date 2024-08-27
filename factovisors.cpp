#include<bits/stdc++.h>
using namespace std;
string solve(long long int factorial, long long int divisor){
    string output;
    long long int biggestDivisor = floor(sqrt(divisor));
    vector<int> factors(biggestDivisor + 1, 0);
    long long int rest = divisor;
    //cout << biggestDivisor << endl;
    long long int bigDivisor = 1;
    if (2 <= biggestDivisor){
        while (rest > 1){
            if (rest % 2 == 0){
                rest/= 2;
                factors[2]++;
            }
            else {
                break;
            }
        }
    }
    long long int index = 3;
    while(index <= biggestDivisor){
        if (rest % index == 0){
            factors[index]++;
            rest/=index;
            if (rest == 1){
                break;
            }
        }
        else {
            index+=2;
        }
    } 
    if (rest > 1){
        //factors[rest] = 1;
        //biggestDivisor = rest;
        bigDivisor = rest;
    }
/*
    if (biggestDivisor > factorial){
        output = to_string(divisor) + " does not divide " +to_string(factorial) +"!"; 
        return output;
    }    
*/
    //cout << "factorisation is done " << endl;
    bool canDivide = true;
    long long int factor;
    long long int factorialFactor = 0;
    output = to_string(divisor) + " does not divide " +to_string(factorial) +"!"; 
    for (int i = 2; i <= biggestDivisor; i++){
/*
        if (factors[i] > 0){
            //cout << i << " " <<factors[i] << endl;
        }
*/
        if (factors[i] > 0){
            factor = i;
            factorialFactor = 0;
            while (factor <= factorial){
                factorialFactor += factorial/factor;
                factor = factor*i;
            }

            if (factorialFactor < factors[i]){
                canDivide = false;
                break;
            }
        }
    } 
    //cout << bigDivisor << " " << factorial << endl;
    if (bigDivisor > factorial){
       canDivide = false;
    }
    if (factorial == 0){
        if (divisor == 1){
            canDivide = true;
        }
    }
    
    if (divisor == 0){
        canDivide = false;
    }
    if (canDivide) {
       output = to_string(divisor) + " divides " +to_string(factorial) +"!";
    }
    else {
        output = to_string(divisor) + " does not divide " +to_string(factorial) +"!"; 

    }
    return output;
}  


int main(){
    string input,output;
    long long int factorial, divisor;
    //long long int secondHighest = floor(tmp);
    while (getline(cin,input)){
        if (input == ""){
           continue;
        } 
        stringstream ss;
        ss << input;
        //cout << "input " << input << endl;
        ss >> factorial;
        ss >> divisor;
        output = solve(factorial,divisor);
        cout << output << endl;
         
    }
    cout << endl;
    return 0;
}
