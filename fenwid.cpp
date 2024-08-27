//Author: Axel Ahlqvist
//Problem: 1.5 Prefix sums 
//A datastructure that handles the operations add and number sum where number
//sum returns the sum of the elements from 0 to the index given. 
//Algorithm: Fenwick Tree
//Time complexity: O(Q Log N) Where Q is the number of operations and 
//N is the length of the array that the operations are performed on.

#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//A FenwickTree is a data structure that handles the operations add and 
//Number sum effiencently by storing intermediate sums.
class FenwickTree {
public:
    FenwickTree(int size) : tree(size + 1, 0) {}

    void add(int i, long long delta) {
        i++;
        //Continue adding to first nodes of the other branches
        while (i < tree.size()) {
            tree[i] += delta;
            i += i & -i;
        }
    }

    long long numberSum(int i) {
        long long result = 0;
        //Summing up the parent nodes until reaching root.
        while (i > 0) {
            result += tree[i];
            i -= i & -i;
        }
        return result;
    }

private:
    vector<long long> tree;
};

// Function to read input lines as a vector of strings. This is useful for switching 
// between reading from standard input and reading from a test case.
vector<string> readInputLines() {
    vector<string> lines;
    char buffer[50];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        lines.push_back(string(buffer));
    }
    return lines;
}

// Function to handle input from the vector of strings
pair<int, vector<pair<char, pair<int, long long>>>> handleInput(const vector<string>& inputLines) {
    int N, Q;
    sscanf(inputLines[0].c_str(), "%d %d", &N, &Q);
    vector<pair<char, pair<int, long long>>> operations(Q);

    for (int i = 1; i <= Q; ++i) {
        char op;
        int index;
        long long delta;
        if (inputLines[i][0] == '+') {
            sscanf(inputLines[i].c_str(), " %c %d %lld", &op, &index, &delta);
            operations[i - 1] = {op, {index, delta}};
        } else if (inputLines[i][0] == '?') {
            sscanf(inputLines[i].c_str(), " %c %d", &op, &index);
            operations[i - 1] = {op, {index, 0}};
        }
    }
    return {N, operations};
}

// Function to process the operations
vector<long long> processOperations(int N, const vector<pair<char, pair<int, long long>>>& operations) {
    FenwickTree fenwickTree(N);
    vector<long long> results;

    for (const auto& operation : operations) {
        if (operation.first == '+') {
            fenwickTree.add(operation.second.first, operation.second.second);
        } else if (operation.first == '?') {
            results.push_back(fenwickTree.numberSum(operation.second.first));
        }
    }

    return results;
}

// Function to handle output
void handleOutput(const vector<long long>& results) {
    for (const auto& result : results) {
        printf("%lld\n", result);
    }
}

vector<string> testCase1 = {
    "10 4",
    "+ 7 23",
    "? 8",
    "+ 3 17",
    "? 8"
};

//The main function reads input, processes the operations and handles the output.
//The first line of the input contains N and Q where N is the length of the 
//array and Q is the number of operations. The following Q lines contain the
//operations. The operations are either + or ? followed by an index and if the
//operation is + an integer is also given. The code only works for integers.
int main() {
    vector<string> inputLines; 
    inputLines = readInputLines();
    //inputLines = testCase1;
    auto input = handleInput(inputLines);
    int N = input.first;
    const vector<pair<char, pair<int, long long>>>& operations = input.second;

    vector<long long> results = processOperations(N, operations);
    handleOutput(results);

    return 0;
}