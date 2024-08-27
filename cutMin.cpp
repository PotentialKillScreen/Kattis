//Author: Axel Ahlqvist
//Problem: Minimal Cut
//The objectiv is to find a subgraph containing the start node but not
//the end node with smalles total flow to the rest of the original graph.
//Algorithm:Edmonds-Karp algorithm
//Time complexity: O(VE^2) where V is the number of vertices and 
//E the number of edges. 

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

struct Edge {
    int u, v;
    long long capacity, flow;
};

// Function to take input as a vector of strings
//The input is expected to start with a line specifying the number of vertices n,
// the number of edges m, the starting node s and the ending node t.
//Then follows m lines with three integers each, the starting node of the edge, 
//the ending node of the edge and the capacity of the edge.
vector<string> readInput() {
    vector<string> inputLines;
    string line;
    while (getline(cin, line)) {
        inputLines.push_back(line);
    }
    return inputLines;
}

// Function to translate input into appropriate data types.
//Also handles error handling for invalid input such as negative flow values.
tuple<int, int, int, int, vector<Edge>> parseInput(const vector<string>& inputLines) {
    istringstream iss(inputLines[0]);
    int n, m, s, t;
    if (!(iss >> n >> m >> s >> t)) {
        cerr << "Error: Invalid input format for n, m, s, or t." << endl;
        exit(1);
    }

    vector<Edge> edges;
    for (int i = 1; i <= m; ++i) {
        istringstream edgeStream(inputLines[i]);
        int u, v;
        long long capacity;
        if (!(edgeStream >> u >> v >> capacity)) {
            cerr << "Error: Invalid input format for edge " << i << "." << endl;
            exit(1);
        }
        if (capacity < 0) {
            cerr << "Error: Negative flow value for edge " << i << "." << endl;
            exit(1);
        }
        edges.push_back({u, v, capacity, 0});
    }

    return make_tuple(n, m, s, t, edges);
}

// BFS function to find an augmenting path. Uses a queue to keep track of the nodes to visit.
//Starts with the starting node and ends as soon as the end node is reached.
bool bfs(int s, int t, vector<int>& parent, vector<vector<int>>& adj, vector<vector<long long>>& capacity, vector<vector<long long>>& flow) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = s;
    queue<pair<int, long long>> q;
    q.push({s, numeric_limits<long long>::max()});

    while (!q.empty()) {
        int u = q.front().first;
        long long curr_flow = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > flow[u][v]) {
                parent[v] = u;
                long long new_flow = min(curr_flow, capacity[u][v] - flow[u][v]);
                if (v == t) {
                    return true;
                }
                q.push({v, new_flow});
            }
        }
    }

    return false;
}

// Function to execute the Edmonds-Karp algorithm (Max Flow)
long long max_flow(int n, int s, int t, const vector<Edge>& edges, vector<vector<int>>& adj, vector<vector<long long>>& capacity, vector<vector<long long>>& flow) {
    long long total_flow = 0;
    vector<int> parent(n);
    //While there is an augmenting path, update the flow in the network.
    //The path is found using BFS. Then the minimum flow in the path is calculated
    //Then the flow is updated by the minimum flow both in the positive and negative direction.
    while (bfs(s, t, parent, adj, capacity, flow)) {
        long long path_flow = numeric_limits<long long>::max();
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, capacity[u][v] - flow[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += path_flow;
            flow[v][u] -= path_flow;
        }

        total_flow += path_flow;
    }

    return total_flow;
}

// Function to find the minimum cut. Uses the max_flow function to find the max flow in the network. 
vector<int> min_cut(int n, int s, int t, const vector<Edge>& edges) {
    vector<vector<int>> adj(n);
    vector<vector<long long>> capacity(n, vector<long long>(n, 0));
    vector<vector<long long>> flow(n, vector<long long>(n, 0));

    for (const auto& edge : edges) {
        capacity[edge.u][edge.v] += edge.capacity;
        adj[edge.u].push_back(edge.v);
        adj[edge.v].push_back(edge.u);
    }

    max_flow(n, s, t, edges, adj, capacity, flow);

    vector<int> visited(n, 0);
    queue<int> q;
    q.push(s);
    visited[s] = 1;
    //Goes through the network only using edges that are not full to push them
    //to the starting nodes cut. This is since Maximum capacity will be used in 
    //minimum cut.
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v] && capacity[u][v] > flow[u][v]) {
                visited[v] = 1;
                q.push(v);
            }
        }
    }

    vector<int> cut_set;
    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            cut_set.push_back(i);
        }
    }

    return cut_set;
}

// Function to handle the output
//Takes a vector of indexes. Prints the vectors sice and the indexes
//with spaces aned endlines.
void printOutput(const vector<int>& cut_set) {
    cout << cut_set.size() << endl;
    for (int vertex : cut_set) {
        cout << vertex << endl;
    }
}

// ain function that takes the input as a vector of strings,
//parses the input to get the necessary data types, then executes the 
//min_cut function which utilizes the Edmonds-Karp algorith to get the 
//set of vertices that make out a minimum cut. Then prints the output in
// the desired format.
//For the flow capacity, only positive integers can be inputed. 
//In case of wrong formatted input an error is raised.
//The input specifies a flow graph. The is the number of vertices and 
//indexes of the vertices making out the minimum cut.
int main() {
    vector<string> inputLines = readInput();
    auto [n, m, s, t, edges] = parseInput(inputLines);
    vector<int> cut_set = min_cut(n, s, t, edges);
    printOutput(cut_set);
    return 0;
}
