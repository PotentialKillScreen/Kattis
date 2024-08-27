//Author: Axel Ahlqvist
//Problem: 1.6 Polynomial multiplication 
//Algorithm: Fast Fourier Transform
//Time complexity: O(N Log N) Where N is the order of the resulting polynomial


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <complex>
#include <cmath>
#include <cstdio>

using namespace std;

const double PI = acos(-1);

//The first line of the input is the number of testcases. Each testcase consists
//of two polynomials. The first line of each testcase contains the degree of the
//first polynomial. The second line contains the coefficients of the polynomial.
//The third and fourth line contains the corresponding information for the 
//second polynomial.
vector<string> readInputLines() {
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }
    return lines;
}

using cd = complex<double>;

//The Fast Fourier Transform algorithm. Recursively splits the input array into
//two arrays of half the size. One for even-indexed elements and one for 
//odd-indexed elements. Until reaching the base case of an array of size 1.
//The function then combines the results of the two arrays by multiplying the
//odd-indexed elements by a complex number and adding them to the even-indexed
void fft(vector<cd>& a, bool invert) {
    
    int n = a.size();
    if (n == 1) return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);

    //Combining the results of the two vectors. Slightly different operations 
    //depending on whether the fft needs to be inverted or not.
    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        //Scaling the results in the invert step.
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}


//Function to multiply two polynomials using the Fast Fourier Transform on vectors of complex
//numbers.
vector<long long> multiplyPolynomials(int n1, vector<long long> poly1, int n2, vector<long long> poly2) {
    
    int n = 1;
    // Find the nearest power of two greater than or equal to the 
    //sum of the sizes of the input polynomials
    while (n < poly1.size() + poly2.size()) 
        n *= 2;

    vector<cd> f1(n), f2(n);
    for (int i = 0; i < poly1.size(); i++)
        f1[i] = poly1[i];
    for (int i = 0; i < poly2.size(); i++)
        f2[i] = poly2[i];

    fft(f1, false);
    fft(f2, false);
    for (int i = 0; i < n; i++)
        f1[i] *= f2[i];
    fft(f1, true);

    vector<long long> product(n);
    //Translate back into real numbers and round to the nearest integer.
    for (int i = 0; i < n; i++)
        product[i] = round(f1[i].real());

    while (product.size() > 1 && product.back() == 0)
        product.pop_back();

    return product;
}

//Function to handle the input and run the MultiplyPolynomials function for 
//each testcase. Handles inconsistent errors.
vector<vector<long long>> multiplyMultiplePolynomials(const vector<string> inputLines) { 
    int n1,n2;
    string inputLine = inputLines[0];
    int nTestCases = stoi(inputLine);
    int index = 1;
    vector<vector<long long>> results(nTestCases);
    for (int i = 0; i < nTestCases; ++i) {
        stringstream ss1(inputLines[index]);
        ss1 >> n1;
        vector<long long > poly1(n1 + 1);
        index++;
        stringstream ss2(inputLines[index]);
        
        for (int j = 0; j <= n1; ++j) {
            if (!(ss2 >> poly1[j])) {
                throw runtime_error("Error: Number of coefficients for polynomial 1 does not match its degree.");
            }
        }
        string extra;
        if (ss2 >> extra) {
            throw runtime_error("Error: Extra coefficients found for polynomial 1.");
        }
        
        
        index++;
        stringstream ss3(inputLines[index]);
        ss3 >> n2;
        vector<long long > poly2(n2 + 1);
        index++;
        stringstream ss4(inputLines[index]);
        for (int j = 0; j <= n2; ++j) {
            if (!(ss4 >> poly2[j])) {
                throw runtime_error("Error: Number of coefficients for polynomial 2 does not match its degree.");
            }
        }
        if (ss4 >> extra) {
            throw runtime_error("Error: Extra coefficients found for polynomial 2.");
        }
        
        vector<long long> product(n2+n1+1);;
        product = multiplyPolynomials(n1, poly1, n2, poly2);
        results[i] = product;
        
    }
    return results;
}

//The output for each testcase consists of the degree of the resulting 
//polynomial followed by a line with the coeffeieces of the resulting 
//polynomial.
void handleOutput(const vector<vector<long long>>& result) {
    for (int i = 0; i < result.size(); ++i) {
        int degree = result[i].size() - 1;
        cout << degree << "\n";
        for (int j = 0; j <= degree; ++j) {
            if (j > 0) cout << " ";
            cout << result[i][j];
        }
    cout << "\n";
    }
    
}

vector<string> testCase1 = {
   "1",
   "2",
   "1 0 5",
   "1",
   "0 -2"
};

vector<string> testCase2 = {
    "1",
    "2",
    "3 2 1",
    "2",
    "1 1 1"
};

vector<string> testCase3 = {
    "1",
    "2",
    "-1 0 1",
    "2",
    "4 -3 2"
};

vector<string> testCase4 = {
    "1",
    "4",
    "5 0 0 0 1",
    "2",
    "2 0 3"
};

vector<string> testCase5 = {
    "1",
    "5",
    "1 2 3 4 5 6",
    "5",
    "6 5 4 3 2 1"
};

vector<string> testCase6 = {
    "1",
    "3",
    "0 0 0 0",
    "3",
    "0 0 0 0"
};

vector<string> testCase7 = {
    "1",
    "0",
    "7",
    "0",
    "3"
};

//The main function reads input, processes the operations and handles the output.
//The order and number of coeffients needs to correspond. Additionally the input
//needs to be integer coefficients making the output also integers.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<string> inputLines;
    inputLines = readInputLines();
    //inputLines = testCase1;
    vector<vector<long long>> results = multiplyMultiplePolynomials(inputLines);
    handleOutput(results);

    return 0;
}