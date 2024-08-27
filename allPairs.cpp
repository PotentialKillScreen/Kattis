//Author: Axel Ahlqvist
//Problem: All Pairs Shortest Path
//Algorithm: Floyd-Warshalls algorithm
//Time complexity: O(N^3) Where N is the number of vertices. 

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <climits>
#include <tuple> 

using namespace std;

const long long INF = LLONG_MAX;

struct Edge {
    int u, v;
    long long w;
};

// Function to take input as a vector of strings
//The input can consist of multiple testcases following eachother.
//Each testcase starts with a line specifying the number of vertices, edges 
//and queries. Followed by m lines specifying the edges. Each edge have
//a cost that can be negative. The last q lines specify the queries.
//The queries are specify two nodes between which the distance is calculated and
//printed. 
vector<string> readInput() {
    vector<string> inputLines;
    string line;
    while (getline(cin, line)) {
        inputLines.push_back(line);
    }
    return inputLines;
}

// Function to translate input into appropriate data types
tuple<vector<Edge>, vector<pair<int, int>>, int, int, int> parseInput(const vector<string>& inputLines, int& index) {
    vector<Edge> edges;
    vector<pair<int, int>> queries;
    int n, m, q;

    istringstream iss(inputLines[index]);
    iss >> n >> m >> q;
    index++;

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        istringstream edgeStream(inputLines[index]);
        edgeStream >> u >> v >> w;
        edges.push_back({u, v, w});
        index++;
    }

    for (int i = 0; i < q; ++i) {
        int u, v;
        istringstream queryStream(inputLines[index]);
        queryStream >> u >> v;
        queries.push_back({u, v});
        index++;
    }

    return make_tuple(edges, queries, n, m, q);
}

// Function to execute the Floyd-Warshall algorithm
vector<vector<long long>> shortest_path_all_pairs(int n, const vector<Edge>& edges) {
    vector<vector<long long>> dist(n, vector<long long>(n, INF));

    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }

    for (const auto& edge : edges) {
        dist[edge.u][edge.v] = min(dist[edge.u][edge.v], edge.w);
    }
    //Go through all vertices and update the distance between them if a shorter
    // path is found by going through another vertex.
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Detect negative cycles
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[k][k] < 0) {
                    dist[i][j] = -INF;
                }
            }
        }
    }

    return dist;
}

// Function to handle the output
void printOutput(const vector<vector<long long>>& dist, const vector<pair<int, int>>& queries) {
    for (const auto& [u, v] : queries) {
        if (dist[u][v] == INF) {
            cout << "Impossible" << endl;
        } else if (dist[u][v] == -INF) {
            cout << "-Infinity" << endl;
        } else {
            cout << dist[u][v] << endl;
        }
    }
    cout << endl;
}

// Function to process all test cases, find the shortest paths and print the output
//to the queries.
void processInput(const vector<string>& inputLines) {
    int index = 0;

    while (index < inputLines.size()) {
        istringstream iss(inputLines[index]);
        int n, m, q;

        // Read the entire line as a string to check for decimals
        string n_str, m_str, q_str;
        iss >> n_str >> m_str >> q_str;

        // Check if any input contains a decimal point
        if (n_str.find('.') != string::npos || m_str.find('.') != string::npos || q_str.find('.') != string::npos) {
            cerr << "Error: Input contains a decimal value." << endl;
            exit(1);
        }

        // Convert strings to integers
        n = stoi(n_str);
        m = stoi(m_str);
        q = stoi(q_str);

        if (n == 0 && m == 0 && q == 0) break;

        auto result = parseInput(inputLines, index);
        vector<Edge> edges;
        vector<pair<int, int>> queries;
        int nn, mm, qq;
        tie(edges, queries, nn, mm, qq) = result;
        vector<vector<long long>> dist = shortest_path_all_pairs(nn, edges);
        printOutput(dist, queries);
    }
}

//Main function that reads the inputLines and then process them.
//The input specify a graph with costs between the vertices (can be negative).
//The process function prints the the shortest path between two vertices.
//In case no path exists between the paths "Impossible" is printed.
//In case of a negative cycle between the vertices.
//Multiple testcases can be follow eachother.
//The input ends with a case starting with the line '0 0 0'.
//Only integers are accepted as edge weights otherwise an error is thrown.
int main() {
    vector<string> inputLines = readInput();
    processInput(inputLines);
    return 0;
}
