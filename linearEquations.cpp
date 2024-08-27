//Author: Axel Ahlqvist
//Problem: Linear Equation Systems with a Unique Solution
//Algorithm: Guassian Elimination
//Time complexity: O(N^3) Where N is the length of the quadratic matrix

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

// Function to read input as vector of strings
// Multiple testcases may be submitted. Each testcase begins with a line
// containing the number of equations n. The next n lines contain the floating
// point coefficients of the n equations. The final line of the testcase
// contains the floating point constants of the n equations.

vector<string> readInput() {
    vector<string> inputLines;
    string line;
    while (getline(cin, line)) {
        inputLines.push_back(line);
    }
    return inputLines;
}

//Function to translate input into appropriate data types
//The input is terminated by a testcase with n = 0
vector<vector<vector<double>>> parseInput(const vector<string>& inputLines) {
    vector<vector<vector<double>>> testCases;
    int index = 0;
    while (index < inputLines.size()) {
        istringstream iss(inputLines[index]);
        int n;
        iss >> n;
        if (n == 0) break;

        vector<vector<double>> testCase;
        testCase.push_back({(double)n});
        index++;

        for (int i = 0; i < n; i++) {
            vector<double> row;
            istringstream rowStream(inputLines[index]);
            double value;
            while (rowStream >> value) {
                row.push_back(value);
            }
            testCase.push_back(row);
            index++;
        }

        vector<double> b;
        istringstream bStream(inputLines[index]);
        double value;
        while (bStream >> value) {
            b.push_back(value);
        }
        testCase.push_back(b);
        index++;

        testCases.push_back(testCase);
    }
    return testCases;
}


// Function to calculate the rank of a matrix in order to distinguish between
// the degenerate cases of inconsistent and multiple solutions.
int calculateRank(vector<vector<double>> mat) {
    int n = mat.size();
    int m = mat[0].size();
    int rank = 0;

    for (int row = 0; row < n; row++) {
        bool nonZero = false;
        for (int col = 0; col < m; col++) {
            if (fabs(mat[row][col]) > 1e-9) {
                nonZero = true;
                for (int k = row + 1; k < n; k++) {
                    double factor = mat[k][col] / mat[row][col];
                    for (int j = col; j < m; j++) {
                        mat[k][j] -= factor * mat[row][j];
                    }
                }
                break;
            }
        }
        if (nonZero) rank++;
    }
    return rank;
}


// Function to execute guass ellimination and back substitution
vector<string> solveEquations(const vector<vector<vector<double>>>& testCases) {
    vector<string> results;
    for (const auto& testCase : testCases) {
        int n = (int)testCase[0][0];
        vector<vector<double>> A(n, vector<double>(n));
        vector<double> b(n);
        vector<double> x(n, 0);
        
        // Fill matrix A and vector b
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[i][j] = testCase[i + 1][j];
            }
            b[i] = testCase[n + 1][i];
        }

        bool inconsistent = false;
        bool multiple = false;

        vector<vector<double>> augmentedMatrix(n, vector<double>(n + 1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                augmentedMatrix[i][j] = A[i][j];
            }
            augmentedMatrix[i][n] = b[i];
        }

        // Calculate rank of A and [A|b]
        int rankA = calculateRank(A);
        int rankAugmented = calculateRank(augmentedMatrix);

        if (rankA < rankAugmented) {
            results.push_back("inconsistent");
            continue;
        } else if (rankA == rankAugmented && rankA < n) {
            results.push_back("multiple");
            continue;
        }

        // Perform Gaussian elimination
        for (int i = 0; i < n; ++i) {
            int maxRow = i;
            for (int k = i + 1; k < n; ++k) {
                if (fabs(A[k][i]) > fabs(A[maxRow][i])) {
                    maxRow = k;
                }
            }

            // Swap rows
            swap(A[i], A[maxRow]);
            swap(b[i], b[maxRow]);

            for (int k = i + 1; k < n; ++k) {
                double factor = A[k][i] / A[i][i];
                b[k] -= factor * b[i];
                for (int j = i; j < n; ++j) {
                    A[k][j] -= factor * A[i][j];
                }
            }
        }

        // Back substitution
        for (int i = n - 1; i >= 0; --i) {
            double sum = b[i];
            for (int j = i + 1; j < n; ++j) {
                sum -= A[i][j] * x[j];
            }
            x[i] = sum / A[i][i];
        }

        // Format the result
        ostringstream oss;
        for (int i = 0; i < n; ++i) {
            if (i > 0) oss << " ";
            oss << x[i];
        }
        string result = oss.str();
        results.push_back(result);
    }
    return results;
}

// Function to handle the output
void printResults(const vector<string>& results) {
    for (const auto& result : results) {
        cout << result << endl;
    }
}

vector<string> testCase1 = {
    "3",
    "1 1 0",
    "3 3 0",
    "0 1 2",
    "1 4 8",
    "0"
};
vector<string> testCase2 = {
    "2",
    "1 1",
    "0 1",
    "23 42",
    "1",
    "5",
    "1",
    "3",
    "1 -2 0",
    "2 -4 0",
    "1 -2 1",
    "3 6 4",
    "3",
    "1 1 0",
    "3 3 0",
    "0 1 2",
    "1 4 8",
    "0"
};



vector<string> testCase3 = {
    "3",
    "1 1 1",
    "1 1 1",
    "1 1 1",
    "1 1 1",
    "0"
};

vector<string> testCase4 = {
    "3",
    "1 1 1",
    "1 1 1",
    "1 1 1",
    "1 1 2",
    "0"
};


//The main function reads input, Translates the vector of strings into a vector
//of testcases and then runs the solveEquations function to use gaussian 
//elimination to solve the cases. The code handles floating coeffiencts and 
//constants. The solution to the equations are printed. In case of a 
//degenerate equation the code distinguish between 'multiple' solution and 
//'inconsistent' equations without solutions.
int main() {
    // Step 1: Read input as vector of strings
    vector<string> inputLines = readInput();
    //vector<string> inputLines = testCase4;

    // Step 2: Translate input into appropriate data types
    vector<vector<vector<double>>> testCases = parseInput(inputLines);
    
    // Step 3: Execute the algorithm
    vector<string> results = solveEquations(testCases);
    
    // Step 4: Handle the output
    printResults(results);
    
    return 0;
}
