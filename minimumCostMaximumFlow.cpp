//Author: Axel Ahlqvist
//Problem: Minimal cost maximum flow
//The objectiv is to find the maximum flow from the start node to the end node
//with the smallest possible cost.
//Algorithm: Successive Shortest Path Algorithm using Bellman-Ford for finding shortest paths in residual graph
// Time complexity: O(V^2 * E^2) where V is the number of vertices and E the number of edges.
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <sstream>

using namespace std;

struct Edge {
    int v, capacity, cost, flow, rev;
};

class Graph {
    int V;
    vector<vector<Edge>> adj;

public:
    Graph(int V);
    void addEdge(int u, int v, int capacity, int cost);
    bool bellmanFord(int s, int t, vector<int>& dist, vector<int>& parent, vector<int>& parentEdge);
    Graph minCostMaxFlowGraph(int s, int t);
    pair<long long, long long> calculateFlowAndCost(int s);
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int capacity, int cost) {
    Edge a{v, capacity, cost, 0, (int)adj[v].size()};
    Edge b{u, 0, -cost, 0, (int)adj[u].size()};
    adj[u].push_back(a);
    adj[v].push_back(b);
}

// Bellman-Ford algorithm to find the shortest path in terms of cost
// Returns true if there is a path from s to t, and also updates the dist, parent, and parentEdge vectors
bool Graph::bellmanFord(int s, int t, vector<int>& dist, vector<int>& parent, vector<int>& parentEdge) {
    fill(dist.begin(), dist.end(), INT_MAX);
    dist[s] = 0;
    bool updated;
    
    for (int i = 0; i < V - 1; ++i) {
        updated = false;
        for (int u = 0; u < V; ++u) {
            for (size_t j = 0; j < adj[u].size(); ++j) {
                Edge &e = adj[u][j];
                if (e.flow < e.capacity && dist[u] != INT_MAX && dist[u] + e.cost < dist[e.v]) {
                    dist[e.v] = dist[u] + e.cost;
                    parent[e.v] = u;
                    parentEdge[e.v] = j;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }
    return dist[t] != INT_MAX;
}

// Function to find the minimum cost maximum flow in the graph
// Returns a new graph containing only the edges used in the maximum flow with their flows set
Graph Graph::minCostMaxFlowGraph(int s, int t) {
    vector<int> dist(V), parent(V), parentEdge(V);
    Graph result(V);
    //While an augmenting path can be found with bellmanFord(), update the flow in the network
    while (bellmanFord(s, t, dist, parent, parentEdge)) {
        int pathFlow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            int edgeIndex = parentEdge[v];
            pathFlow = min(pathFlow, adj[u][edgeIndex].capacity - adj[u][edgeIndex].flow);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            int edgeIndex = parentEdge[v];
            adj[u][edgeIndex].flow += pathFlow;
            adj[v][adj[u][edgeIndex].rev].flow -= pathFlow;
        }
    }
    // Set flow in the result graph
    for (int u = 0; u < V; ++u) {
        for (const Edge &e : adj[u]) {
            if (e.flow > 0) {
                result.addEdge(u, e.v, e.capacity, e.cost);
                result.adj[u].back().flow = e.flow; 
            }
        }
    }
    
    return result;
}

//Takes a graph and outputs the total flow and cost of the flow
pair<long long, long long> Graph::calculateFlowAndCost(int s) {
    long long flow = 0, cost = 0;
    for (int u = 0; u < V; ++u) {
        for (const Edge &e : adj[u]) {
            if (e.flow > 0) {
                //Count the flow from the source node
                if (u == s) 
                    flow += e.flow;
                cost += e.flow * e.cost;
            }
        }
    }
    return {flow, cost};
}


// Function to take input as a vector of strings
//The input is expected to start with a line specifying the number of vertices n,
// the number of edges m, the starting node s and the ending node t.
//Then follows m lines with four integers each, the starting node,
//the ending node, the capacity and the cost of the edge.
vector<string> readInput() {
    vector<string> inputLines;
    string line;
    while (getline(cin, line)) {
        inputLines.push_back(line);
    }
    return inputLines;
}

Graph max_flow(Graph& g, int s, int t) {
    return g.minCostMaxFlowGraph(s, t);
}

//Process the input lines. Assigns s, and t and adds edges to the graph g.
void processInput(const vector<string>& inputLines, Graph& g, int& s, int& t) {
    istringstream iss(inputLines[0]);
    int n, m;
    iss >> n >> m >> s >> t;

    g = Graph(n);

    for (int i = 1; i <= m; ++i) {
        istringstream edgeStream(inputLines[i]);
        int u, v, c, w;
        edgeStream >> u >> v >> c >> w;
        g.addEdge(u, v, c, w);
    }
}
//Calculates the flow and cost of the resulting graph and prints them.
void printOutput(Graph& resultGraph, int s, int t) {
    auto [flow, cost] = resultGraph.calculateFlowAndCost(s);
    cout << flow << " " << cost << endl;
}

vector<string> testCase1 = {
    "4 4 0 3",
    "0 1 4 10",
    "1 2 2 10",
    "0 2 4 30",
    "2 3 4 10"
};

//Main function that takes the input as a vector of strings,
//parses the input to assign variables and build the graph, then executes the 
//max_flow function which uses successive Shortest Path Algorithm using Bellman-Ford
//to return a graph with the maximum flow at the minimum cost.
//The PrintOutput function then prints the flow and cost of the resulting graph.
int main() {
    vector<string> inputLines = readInput();
    //vector<string> inputLines = testCase1;
    Graph g(0);
    int s, t;
    processInput(inputLines, g, s, t);
    Graph resultGraph = max_flow(g, s, t);
    printOutput(resultGraph, s, t);
    return 0;
}
