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
    PrimeGenerator(int);
    int max;
    int nCandidates;
    int nIntervallPrimes;
    vector<bool> isPrime;
    vector<int> candidates;
    vector<bool> isHappy;
    void set_initial_values(int);
    void generate_primes();
    void count_primes();
    void solve(int);
    void checkHappy();
};

PrimeGenerator::PrimeGenerator(int nCandidates){
    //Constructs the class and generates and counts the primes
    PrimeGenerator::set_initial_values(nCandidates);
    PrimeGenerator::generate_primes();
    PrimeGenerator::checkHappy();
    //PrimeGenerator::count_primes();
}

void PrimeGenerator::set_initial_values(int nCandidates){
    //Creates a bool vector to keep track of which numbers are prime and not.
    //Initially all number are assumed to be prime
    int tmp; 
    PrimeGenerator::nCandidates = nCandidates;
    PrimeGenerator::max = 10000;
    candidates.clear();
    for (int i = 0; i <nCandidates; i++){
       cin >> tmp; 
       cin >> tmp;
       candidates.push_back(tmp); 
    }
    isHappy.clear(); 
    isPrime.clear();
    for (int i = 0; i<=max; i++){
        isPrime.push_back(true);
        isHappy.push_back(false);
    }
}

void PrimeGenerator::generate_primes(){
    //Iterates over all primes to exclude the number which are divisible by primes
    int size = max-1;
    int index = 2;
    isPrime[0] = false;
    isPrime[1] = false;
    while(index < max/2){
        if (isPrime[index] == false){
            index++;    
            continue;
        }
        for (int i = 2*index; i<=max;i+=index){
            isPrime[i] = false;         
        }
        index++; 
    }
}

        
void PrimeGenerator::count_primes(){
    //Counts the primes in the vector
    nIntervallPrimes = count(isPrime.begin(), isPrime.end(), true);
}

void PrimeGenerator::checkHappy(){
    int tmp, sum, temp;
    vector<int> passedValues;
    vector<int> digits(5, 0);
    for (int i = 0; i <nCandidates; i++){
        passedValues.clear();
        cout << i +1 << " " << candidates[i] << " ";
        tmp = candidates[i];
        if (!isPrime[tmp]){
            cout << "NO" << endl;
            continue; 
        }
        if (isHappy[tmp]){
            //cout << "tmp " << tmp << endl;
            cout << "YES" << endl;
            continue;
    
        }
        while(true){
            if (count(passedValues.begin(), passedValues.end(), tmp)){
                cout << "NO" << endl;
                break;
            }
            sum = 0;
            passedValues.push_back(tmp);
            
            for (int j =0; j<5; j++){
                temp = tmp/(pow(10,j));
                temp = temp%10;
                temp = pow(temp,2);
                sum += temp;
                //sum+= pow((tmp/(pow(10,j)))%10,2);  
            }
            tmp = sum;
            if (tmp == 1 || isHappy[tmp]){
                //cout << "tmp " << tmp << endl;
                cout << "YES" << endl;
               for (int j =0; j<passedValues.size();j++){
                    //cout << "passed " << passedValues[j] << endl;
                    isHappy[passedValues[j]] = true; 
               }
               break;
            }
        }
        
    }
}
int main() {
    int nCandidates;
    cin >> nCandidates;
    PrimeGenerator primeGenerator(nCandidates); 
    
    
     


    int maxNumber, nPrimes;
    vector<int> testPrimes;
//input
    //cin >> nPrimes;
    //for (int i= 0; i < nPrimes; i++){
    //    cin >> tmp; 
    //    testPrimes.push_back(tmp);
    //}
//Using the algorithm
    //PrimeGenerator primeGenerator(maxNumber);
// Output
    //cout << primeGenerator.nIntervallPrimes << endl;
    //for (int i = 0; i <nPrimes; i++){
    //    cout << primeGenerator.isPrime[testPrimes[i]] << endl; 
    //} 
    cout << endl; 
    return 0;
}
