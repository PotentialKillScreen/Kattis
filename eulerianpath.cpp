//Author: Axel Ahlqvist
//Problem: 2.9 Euler Path
//The objective is to find a path that visits every edge exactly once.
//Algorithm: Hierholzer’s algorithm
// Time complexity: O(E + V) where V is the number of vertices and E the number of edges.

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef long long int ll;

struct Edge {
    int u, v;
    Edge(int u, int v) : u(u), v(v) {}
};

struct Graph {
    int n;  // number of nodes
    int m;  // number of edges
    unordered_map<int, vector<Edge>> adj;  // adjacency list of edges
    unordered_map<int, int> in_degree;
    unordered_map<int, int> out_degree;
};

// Function to read input as a vector of strings
// Multiple test cases can follow each other.
// Each test case starts with a line containing two integers n and m, 
//where n is the number of nodes and m is the number of edges.
//Then m lines follow, each containing two integers u and v specifying an 
//edge between the vertices. Can't add the same edge twice.
vector<string> read_input() {
    vector<string> input;
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }
    return input;
}


struct EdgeHash {
    size_t operator()(const pair<int, int>& edge) const {
        return hash<int>()(edge.first) ^ hash<int>()(edge.second);
    }
};

// Function to parse input, create a graph for each testCase and return the 
//graphs in  a vector.
vector<Graph> parse_input(const vector<string>& input) {
    vector<Graph> graphs;
    size_t index = 0;
    while (index < input.size()) {
        int n, m;
        if (sscanf(input[index].c_str(), "%d %d", &n, &m) != 2) {
            ++index;
            continue;
        }
        if (n == 0 && m == 0) break;
        Graph graph;
        graph.n = n;
        graph.m = m;
        for (int i = 0; i < m; ++i) {
            int u, v;
            sscanf(input[index + 1 + i].c_str(), "%d %d", &u, &v);
            graph.adj[u].emplace_back(u, v);
            graph.out_degree[u]++;
            graph.in_degree[v]++;
        }
        index += m + 1; // move index past the current test case
        graphs.push_back(graph);
    }
    return graphs;
}

// Function to find Eulerian path using Hierholzer's algorithm
vector<Edge> eulerian_path(Graph& graph) {
    // Find start node with (out - in) == 1, and end node with (in - out) == 1
    int start = -1, end = -1;
    for (int i = 0; i < graph.n; ++i) {
        if (graph.out_degree[i] - graph.in_degree[i] == 1) {
            if (start == -1) start = i;
            else return {}; // more than one start node
        }
        if (graph.in_degree[i] - graph.out_degree[i] == 1) {
            if (end == -1) end = i;
            else return {}; // more than one end node
        }
    }
    if ((start == -1) != (end == -1)) return {}; // start and end do not match
    
    // If no specific start node then graph is one or more cycles find a node with an edge
    if (start == -1) {
        for (int i = 0; i < graph.n; ++i) {
            if (graph.out_degree[i] > 0) {
                start = i;
                break;
            }
        }
    }
    if (start == -1) return {}; // no edges in graph
    
    //As long as all edges are part of the same cycle, the graph has an 
    //Eulerian path.
    //The algorithm goes through the graph while deleting visiting edges, until
    //A dead end is reached. This must be the final step. The algorithm 
    //goes back one steps top check other paths.
    //This process is continued until the longest possible path from starting 
    //node has been recorded backwards in path.
    vector<Edge> path;
    stack<int> curr_path;
    unordered_map<int, int> edge_count;
    for (int i = 0; i < graph.n; ++i) {
        edge_count[i] = graph.adj[i].size();
    }
    stack<Edge> curr_edge_path; 
    curr_path.push(start);
    int curr_v = start;
    Edge next_edge = graph.adj[curr_v].back();
    while (!curr_path.empty()) {
        if (edge_count[curr_v] > 0) {
            curr_path.push(curr_v);

            next_edge = graph.adj[curr_v].back();
            curr_edge_path.push(next_edge);
            graph.adj[curr_v].pop_back();
            edge_count[curr_v]--;
            curr_v = next_edge.v;
            
        } else {
            if (!curr_edge_path.empty()) {
                path.push_back(curr_edge_path.top());
                curr_edge_path.pop();
            }
            curr_v = curr_path.top();
            curr_path.pop();
        }
    }
    // Reverse the path to get the order from start to end.
    reverse(path.begin(), path.end());
    if (path.size() == graph.m) return path;
    else return {}; // Not all edges were used
}

// Function to take a vector of results, each consisting of a vector of 
//edges. For each test case prints either 'Impossible' or the vertices 
//making out the Eulerian path.
void print_output(const vector<vector<Edge>>& results) {
    for (const auto& result : results) {
        if (result.empty()) {
            cout << "Impossible" << endl;
        } else {
            for (size_t i = 0; i < result.size(); ++i) {
                if (i > 0) cout << " ";
                cout << result[i].u;
                if (i == result.size() - 1) cout << " " << result[i].v;
            }
            cout << endl;
        }
    }
}

vector<string> testCase4 = {
    "4 6",
    "0 1",
    "1 2",
    "2 1",
    "1 0",
    "1 3",
    "3 1",
    "0 0"
};

vector<string> testCase5 = {
    "3 2",
    "0 1",
    "1 2",
    "0 0"
};

vector<string> testCase6 = {
    "2 2",
    "0 1",
    "0 1",
    "0 0"
};

//Main function that takes the input as a vector of strings,
//parses the input to create a graph for each testcase.
//For each graph, calculate the vector of edges making out the 
//eulerian_path. If there is no such path the function returns an 
//empty vector.
//The results are saved in a vector, finally the result is printed in 
//the desired format.
int main() {
    vector<string> input = read_input();
    //vector<string> input = testCase6;
    vector<Graph> graphs = parse_input(input);
    vector<vector<Edge>> results;
    for (auto& graph : graphs) {
        vector<Edge> result = eulerian_path(graph);
        results.push_back(result);
    }
    print_output(results);
    return 0;
}