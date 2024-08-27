//Author: Axel Ahlqvist
//Problem: Maximum Flow
//Algorithm: Edmonds-Karp algorithm
//Time complexity: O(VE^2) where V is the number of vertices and 
//E the number of edges. 

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <climits>
#include <queue>
#include <tuple>

using namespace std;

struct Edge {
    int u, v;
    long long capacity;
    long long flow;
};

class Graph {
public:
    int V;
    vector<Edge> edges;
    vector<vector<int>> adj;

    Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v, long long capacity) {
        edges.push_back({u, v, capacity, 0});
        adj[u].push_back(edges.size() - 1);
        adj[v].push_back(edges.size() - 1);  // Reverse edge index
    }

    Graph getResidualGraph() const {
        Graph residualGraph(V);
        for (const auto& edge : edges) {
            residualGraph.addEdge(edge.u, edge.v, edge.capacity);
        }
        return residualGraph;
    }
    void buildGraph(const vector<Edge>& edges) {
        for (const auto& edge : edges) {
            addEdge(edge.u, edge.v, edge.capacity);
        }
    }

    // Breath first seach to find an augmenting path
    bool bfs(int s, int t, vector<int>& parent, vector<vector<long long>>& capacity, vector<vector<long long>>& flow) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = s;
        queue<pair<int, long long>> q;
        q.push({s, LLONG_MAX});

        while (!q.empty()) {
            int u = q.front().first;
            long long curr_flow = q.front().second;
            q.pop();

            for (int idx : adj[u]) {
                int v = edges[idx].u == u ? edges[idx].v : edges[idx].u;
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
    pair<long long, Graph> maxFlow(int s, int t) {
        vector<vector<long long>> capacity(V, vector<long long>(V, 0));
        vector<vector<long long>> flow(V, vector<long long>(V, 0));

        for (const auto& edge : edges) {
            capacity[edge.u][edge.v] += edge.capacity;
        }

        long long total_flow = 0;
        vector<int> parent(V);
        //While an augmenting path can be found with bfs(), update the flow in the network
        // both in the positive and negative direction.
        while (bfs(s, t, parent, capacity, flow)) {
            long long path_flow = LLONG_MAX;
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
        //Add the used edges to the resultGraph
        Graph resultGraph(V);
        for (const auto& edge : edges) {
            if (flow[edge.u][edge.v] > 0) {
                resultGraph.addEdge(edge.u, edge.v, edge.capacity);
                resultGraph.edges.back().flow = flow[edge.u][edge.v];
            }
        }

        return {total_flow, resultGraph};
    }
};

// Function to read input and return it as a vector of strings
vector<string> readInput() {
    vector<string> inputLines;
    string line;
    while (getline(cin, line)) {
        inputLines.push_back(line);
    }
    return inputLines;
}

// Function to translate the inputLinse into appropriate data types
tuple<int, int, int, int, vector<Edge>> parseInput(const vector<string>& inputLines) {
    istringstream iss(inputLines[0]);
    int n, m, s, t;
    iss >> n >> m >> s >> t;

    vector<Edge> edges;
    for (int i = 1; i <= m; ++i) {
        istringstream edgeStream(inputLines[i]);
        int u, v;
        long long capacity;
        edgeStream >> u >> v >> capacity;
        edges.push_back({u, v, capacity, 0});
    }

    return make_tuple(n, m, s, t, edges);
}

//Takes the resulting graph and and calculates the max flow from
//Prints the number of vertices, the max flow and the number of edges used 
//in the max flow Then prints each of those edges.
void printOutput(int n, const Graph& resultGraph,int s) {
    long long maxFlow = 0;
      for (const auto& edge : resultGraph.edges) {
        if(edge.u == s){
            maxFlow += edge.flow;
        }
    }
    vector<Edge> usedEdges = resultGraph.edges;
    cout << n << " " << maxFlow << " " << usedEdges.size() << endl;
    for (const auto& edge : usedEdges) {
        if (edge.flow > 0) {
            cout << edge.u << " " << edge.v << " " << edge.flow << endl;
        }
    }
}

//Take the original graph and return the resulting graph with the max flow.
Graph max_flow(Graph G, int s, int t) {
    auto [maxFlow, resultGraph] = G.maxFlow(s, t);
    return resultGraph;
}


// Main function that takes the input as a vector of strings,
//parses the input to get the necessary data types, then executes the 
//Edmonds-Karp algorithm and finally prints the output in the desired format.
int main() {
    vector<string> inputLines = readInput();
    auto [n, m, s, t, edges] = parseInput(inputLines);
    Graph g(n);
    g.buildGraph(edges);
    Graph resultGraph = max_flow(g, s, t);
    printOutput(n, resultGraph,s);

    return 0;
}
