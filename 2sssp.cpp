//Author: Axel Ahlqvist
//Problem: 2.2 Single Source Shortest Path: Time Table Graphs
//Algorithm: Djikstra's Algorithm
//Time complexity: O((N+Q)LOG(N)) Where N is the number of vertices and Q The number of edges. 
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>
#include <climits>
#include <tuple>
#include <iomanip>

using namespace std;

struct Edge {
    int u, v, t0, P, d;
};

// Function to take input as a vector of strings
vector<string> readInput() {
    vector<string> inputLines;
    string line;
    while (getline(cin, line)) {
        inputLines.push_back(line);
    }
    return inputLines;
}

// Function to translate input into appropriate data types
tuple<vector<tuple<int, int, int, int, int>>, vector<int>, int, int, int, int> parseInput(const vector<string>& inputLines, int& index) {
    vector<tuple<int, int, int, int, int>> edges;
    vector<int> queries;
    int n, m, q, s;

    istringstream iss(inputLines[index]);
    iss >> n >> m >> q >> s;
    index++;

    for (int i = 0; i < m; ++i) {
        int u, v, t0, P, d;
        istringstream edgeStream(inputLines[index]);
        edgeStream >> u >> v >> t0 >> P >> d;
        edges.emplace_back(u, v, t0, P, d);
        index++;
    }

    for (int i = 0; i < q; ++i) {
        int query;
        istringstream queryStream(inputLines[index]);
        queryStream >> query;
        queries.push_back(query);
        index++;
    }

    return make_tuple(edges, queries, n, m, q, s);
}

// Function to execute the algorithm and return distances and parents using 
//djiktstra's algorithm modified to take the time table into account.
//The input is a graph represented as a vector of vectors of tuple and the
//starting node s.A priority queue is used to keep track of the nodes to visit.
//A tuple is returned that contains the distances and the parents of the nodes.
//With the parents of the nodes the shortest path can be reconstructed.
tuple<vector<long long>, vector<int>> shortest_path(const vector<vector<tuple<int, int, int, int>>>& graph, int s) {
    int n = graph.size();
    vector<long long> dist(n, LLONG_MAX);
    vector<int> parent(n, -1);
    dist[s] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    //Place the starting node in the priority queue.
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();
        //If the distance to the node is greater than the current shortest distance
        //the path is irrelevant.
        if (currentDist > dist[u]) continue;
        //Else add the neighbors of the node to the priority queue.
        for (const auto& [v, t0, P, d] : graph[u]) {
            if (P == 0) {
                if (currentDist <= t0) {
                    long long newDist = t0 + d;
                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        parent[v] = u;
                        pq.emplace(newDist, v);
                    }
                }
            } else {
                long long arrivalTime = t0;
                if (currentDist > t0) {
                    //Add wait time until next departure
                    arrivalTime = t0 + ((currentDist - t0 + P -1) / P) * P;
                }
                long long newDist = arrivalTime + d;

                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    parent[v] = u;
                    pq.emplace(newDist, v);
                }
            }
        }
    }

    return make_tuple(dist, parent);
}

// Function to print the output
void printOutput(const vector<vector<long long>>& allResults) {
    for (const auto& results : allResults) {
        for (const auto& result : results) {
            if (result == -1) {
                cout << "Impossible" << endl;
            } else {
                cout << result << endl;
            }
        }
        cout << endl;
    }
}

//Function to process all test cases, parse the test cases input
//and exceute the shortest_path algorithm.
vector<vector<long long>> processInput(const vector<string>& inputLines) {
    vector<vector<long long>> allResults;
    int index = 0;

    while (index < inputLines.size()) {
        istringstream iss(inputLines[index]);
        int n, m, q, s;
        iss >> n >> m >> q >> s;
        if (n == 0 && m == 0 && q == 0 && s == 0) break;

        auto [edges, queries, nn, mm, qq, ss] = parseInput(inputLines, index);
        vector<vector<tuple<int, int, int, int>>> graph(nn);

        for (const auto& [u, v, t0, P, d] : edges) {
            graph[u].emplace_back(v, t0, P, d);
        }

        auto [dist, parent] = shortest_path(graph, ss);

        vector<long long> results;
        for (const auto& query : queries) {
            results.push_back(dist[query] == LLONG_MAX ? -1 : dist[query]);
        }

        allResults.push_back(results);
    }

    return allResults;
}

vector<string> testCase1 = {
   "4 4 4 0",
   "0 1 15 10 5",
   "1 2 15 10 5",
   "0 2 5 5 30",
   "3 0 0 1 1",
   "0",
   "1",
   "2",
   "3",
   "2 1 1 0",
   "0 1 100 0 5",
   "1",
   "0 0 0 0"
};
//expected output:
/*
0
20
30
Impossible

105
*/

// Main function that reads input, processes the input and prints the output.
//The input defines a graph with a time table and queries which are nodes
//that the shortest time to are returned.
//Multiple test cases can be submitted one after the other. The input
//is terminated with a test case starting with '0 0 0 0'.
//The first four integers of each test case are the number of vertices,
//edges, queries and the starting vertex. The following m lines are the
//edges. Each edge is represented by five integers. The first two are the
//vertices the edge connects. The third is the time the edge is available
//to be used. The fourth is the period of the edge and the fifth is the
//time it takes to travel the edge. The following q lines are the queries
//nodes to output the shortest time to reach. In case it is not possible to
//reach the node the output is 'Impossible'.
int main() {
    vector<string> inputLines = readInput();
    //vector<string> inputLines = testCase1;
    vector<vector<long long>> results = processInput(inputLines);
    printOutput(results);
    return 0;
}