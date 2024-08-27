//Author: Axel Ahlqvist
//Problem: 1.3 Longest Increasing Subsequence 
//Finding the longeest sequence of increasing integers in a sequence of integers.
//Algorithm: Dynamic programming and binary search
//Time complexity: O(n log n) where n is the number of integers in the input sequence.

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <sstream>
#include <string>


using namespace std;

using Case = std::vector<int>;

//Processes the input. First an integer with the number of integers in the
//input sequence. Then a line with the input sequence. The sequences
//are put in a vector of cases. New cases are processed until an empty line
//is inputed.
std::vector<Case> processCases() {
    std::vector<Case> Cases;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break;  // Stop reading if an empty line is encountered
        }

        std::istringstream iss(line);
        int n;
        iss >> n;
        
        if (n <= 0 ) {
            std::cerr << "Length needs to be positive" << std::endl;
            continue;
        }

        std::vector<int> sequence(n);
        
        std::getline(std::cin, line);
        std::istringstream seqStream(line);
        for (int i = 0; i < n; ++i) {
            seqStream >> sequence[i];
            if (seqStream.fail()) {
                std::cerr << "Invalid input." << std::endl;
                return {};
            }
        }

        // Add the test case to the vector
        Cases.emplace_back(sequence);
    }

    return Cases;
}



//Algorithm for finding the longest increasing subsequence.
//Uses dynamic programming. Uses the vector prev to recreate the sequence
//The vector LIS keeps track of the smallest integers that create the longest
// increasing subsecquence for each length. Lower_bound is used as it returns 
//the optimal position of the integer in the current LIS in O(log N) time.
vector<int> findLIS(vector<int> &arr) {
    int n = arr.size();
    if (n == 0) {
        return {};
    }

    vector<int> lis, indices(n, -1), prev(n, -1);
    vector<int> pos;

    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(lis.begin(), lis.end(), arr[i]);
        int idx = it - lis.begin();

        if (it == lis.end()) {
            lis.push_back(arr[i]);
            pos.push_back(i);
        } else {
            *it = arr[i];
            pos[idx] = i;
        }

        if (idx > 0) {
            prev[i] = pos[idx - 1];
        }

        indices[idx] = i;
    }

    int lis_length = lis.size();
    vector<int> lis_indices(lis_length);
    int k = indices[lis_length - 1];

    for (int i = lis_length - 1; i >= 0; --i) {
        lis_indices[i] = k;
        k = prev[k];
    }
    return lis_indices;
}

//Prints the output in the desired format. First the number of integers in
//the sequence. Then the indexes of the sequence.
void printOutput(vector<int> &lis) {
    cout << lis.size() << "\n";
    for (int i = 0; i < lis.size(); ++i) {
        cout << lis[i];
        if (i != lis.size() - 1) cout << " ";
    }
    cout << "\n";
    
}

/*
std::vector<Case> Case1 = {
    //{1,2,3,4,5,6,7,8,9,10}
    //,{1,1,1,1,1,1,1,1,1,1}
    {5, 19, 5, 81, 11, 14, 70}
    //{5, 19, 5, 81, 50, 28, 29, 1, 83, 23}
};
*/

//Takes inputs, executes the find longest increasing subsequence and then 
//prints the results in the desired format
int main() {
    int n;
    //std::vector<Case> Cases = Case1;
    std::vector<Case> Cases = processCases();
    int nCases = Cases.size();
    for (int i = 0; i < nCases; i++){
        vector<int> inputSequence = Cases[i];
        vector<int> longestSubsequence;
        longestSubsequence = findLIS(inputSequence);
        printOutput(longestSubsequence);
    }
    return 0;
}