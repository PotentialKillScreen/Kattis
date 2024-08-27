//Author: Axel Ahlqvist
//Problem: Prime Sieve
//Finding all primes up to a given integer
//Algorithm: Sieve of Eratosthenes
//Time complexity: O(NloglogN)
//Memory complexity: O(N)

#include<bits/stdc++.h>
using namespace std;

class PrimeGenerator{
    //class which takes an integer as input and finds every prime up to that integer 
    int maximus;
public:
    int maxNumber;
    int nIntervallPrimes;
    vector<bool> isPrime;
    PrimeGenerator(int);
    void set_initial_values(int);
    void generate_primes();
    void count_primes();
    void solve(int);
};

PrimeGenerator::PrimeGenerator(int max){
    //Constructs the class and generates and counts the primes
    PrimeGenerator::set_initial_values(max);
    PrimeGenerator::generate_primes();
    PrimeGenerator::count_primes();
}

void PrimeGenerator::set_initial_values(int max){
    //Creates a bool vector to keep track of which numbers are prime and not.
    //Initially all number are assumed to be prime
    PrimeGenerator::maxNumber = max;
    isPrime.clear();
    for (int i = 0; i<=max; i++){
        isPrime.push_back(true);
    }
}

void PrimeGenerator::generate_primes(){
    //Iterates over all primes to exclude the number which are divisible by primes
    int size = maxNumber;
    int index = 2;
    isPrime[0] = false;
    isPrime[1] = false;
    while(index < maxNumber/2){
        if (isPrime[index] == false){
            index++;    
            continue;
        }
        for (int i = 2*index; i<=maxNumber;i+=index){
            isPrime[i] = false;         
        }
        index++; 
    }
}

        
void PrimeGenerator::count_primes(){
    //Counts the primes in the vector
    nIntervallPrimes = count(isPrime.begin(), isPrime.end(), true);
}


int main() {
    int maxNumber, nPrimes, tmp;
    vector<int> testPrimes;
//input
    cin >> maxNumber;
    cin >> nPrimes;
    for (int i= 0; i < nPrimes; i++){
        cin >> tmp; 
        testPrimes.push_back(tmp);
    }
//Using the algorithm
    PrimeGenerator primeGenerator(maxNumber);
// Output
    cout << primeGenerator.nIntervallPrimes << endl;
    for (int i = 0; i <nPrimes; i++){
        cout << primeGenerator.isPrime[testPrimes[i]] << endl; 
    } 
    
    return 0;
}
