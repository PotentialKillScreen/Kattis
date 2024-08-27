// Author: Axel Ahlqvist
// Problem: 3.3 Dvaput
// The objective is to find the longest substring that appears at least twice in a string.
// Algorithm: Suffix array construction and LCP (Longest Common Prefix) array computation.
// Time complexity: O(n log n) for suffix array construction and O(n) for LCP array computation.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to read input and return as vector of strings
//The input starts with a line containing an integer L, the length of the string.
//Then follows the string s of length L.
vector<string> readInput() {
    int L;
    string s;
    cin >> L;
    cin >> s;
    return {to_string(L), s};
}

// Function to parse the input vector into appropriate data types
pair<int, string> parseInput(const vector<string>& input) {
    int L = stoi(input[0]);
    string s = input[1];
    return {L, s};
}

// Function to build the suffix array
vector<int> buildSuffixArray(const string& s) {
    int n = s.length();
    vector<int> suffixArray(n), rank(n), tempRank(n);

    // Initialize suffix array and rank
    for (int i = 0; i < n; ++i) {
        suffixArray[i] = i;
        rank[i] = s[i];
    }

    // Iteratively build the suffix array
    for (int k = 1; k < n; k *= 2) {
        auto compare = [&](int a, int b) {
            if (rank[a] != rank[b]) return rank[a] < rank[b];
            int ra = (a + k < n) ? rank[a + k] : -1;
            int rb = (b + k < n) ? rank[b + k] : -1;
            return ra < rb;
        };

        sort(suffixArray.begin(), suffixArray.end(), compare);

        // Update temporary rank
        tempRank[suffixArray[0]] = 0;
        for (int i = 1; i < n; ++i) {
            tempRank[suffixArray[i]] = tempRank[suffixArray[i - 1]];
            if (compare(suffixArray[i - 1], suffixArray[i])) {
                tempRank[suffixArray[i]]++;
            }
        }

        // Copy temporary rank to rank
        rank = tempRank;
    }

    return suffixArray;
}

// Function to build the LCP array
vector<int> buildLCPArray(const string& s, const vector<int>& suffixArray) {
    int n = s.length();
    vector<int> rank(n), lcp(n);

    // Compute the rank array
    for (int i = 0; i < n; ++i) {
        rank[suffixArray[i]] = i;
    }

    // Compute the LCP array
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] > 0) {
            int j = suffixArray[rank[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) {
                h++;
            }
            lcp[rank[i]] = h;
            if (h > 0) h--;
        }
    }

    return lcp;
}

// Function to find the length of the longest repeated substring
int longestRepeatedSubstringLength(const string& s) {
    if (s.empty()) return 0;

    vector<int> suffixArray = buildSuffixArray(s);
    vector<int> lcpArray = buildLCPArray(s, suffixArray);

    // Find the maximum value in the LCP array
    int maxLength = 0;
    for (int length : lcpArray) {
        maxLength = max(maxLength, length);
    }

    return maxLength;
}

// Function to output the result
void outputResult(int result) {
    cout << result << endl;
}

// Main function that orchestrates the reading, parsing, processing, and outputting
int main() {
    // Read input
    vector<string> input = readInput();
    
    // Parse input into appropriate data types
    pair<int, string> parsedInput = parseInput(input);

    // Execute the algorithm to find the longest repeated substring length
    int result = longestRepeatedSubstringLength(parsedInput.second);

    // Output the result
    outputResult(result);

    return 0;
}