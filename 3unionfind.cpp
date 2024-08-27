//Author: Axel Ahlqvist
//Problem: 1.4 Union-Find Longest Increasing Subsequence 
//A datastructure that implements the operations merge, same and find
//Algorithm: Disjoint set union (DSU)
//Time complexity: O(Q log N) where Q is the number of operations and 
//N is the number of elements in the base set.

#include <iostream>
#include <vector>
#include <string>
#include <cstdio> // for faster input and output
#include <sstream>

using namespace std;

//Data structure to handle the operations merge, same and find
class UnionFind {
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    //checks if two elements are in the same set by checking the 
    //rootS of the tree
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    //finds the root of the tree
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    //merges two sets by setting the root of one tree to the
    // root of the other based on rank.
    void merge(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

struct Operation {
    char type;
    int a;
    int b;
};

struct InputData {
    int N;
    int Q;
    vector<Operation> operations;
};

vector<string> handleinput(){
    string line;
    vector<string> input;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break;  // Stop reading if an empty line is encountered
        }
        input.push_back(line);
    }
    return input;
}


InputData translateInput(vector<string> input){
    istringstream iss(input[0]);
    int N,Q;
    InputData inputdata;
    iss >> N >> Q;
    inputdata.N = N;
    inputdata.Q = Q;
    for (int i = 0; i<Q; i++){
        istringstream iss(input[i+1]);
        Operation operation;
        //initialize operation struct with values from iss
        iss >> operation.type >> operation.a >> operation.b;
        inputdata.operations.push_back(operation);
    }
    return inputdata;
}

//Function to process the operations
//Uses merge if operation character is '=' and same if operation 
//character is '?'
vector<string> processOperations(const InputData &inputData) {
    UnionFind uf(inputData.N);
    vector<string> results;
    for (const auto &op : inputData.operations) {
        if (op.type == '=') {
            uf.merge(op.a, op.b);
        } else if (op.type == '?') {
            if (uf.same(op.a,op.b)) {
                results.push_back("yes");
            } else {
                results.push_back("no");
            }
        }
    }
    return results;
}

void handleOutput(const vector<string> &results) {
    for (const auto &result : results) {
        printf("%s\n", result.c_str());
    }
}


vector<string> testcase1 = {"10 4","? 1 3","= 1 8","= 3 8","? 1 3"};


int main(){

    vector<string> input; 
    input = handleinput();
    //input = testcase1;
    InputData inputData = translateInput(input);
    vector<string> results = processOperations(inputData);

    handleOutput(results);
    return 0;
}