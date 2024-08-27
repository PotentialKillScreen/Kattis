//Author: Axel Ahlqvist
//Problem: Single source shortest path, non-negative weights
//Finding the shortest path in a graph
//Algorithm: Dijkstra
//Time complexity: O(m log(n)) 
//Memory complexity(m+n)
#include<bits/stdc++.h>
using namespace std;



//Struct to give both the minimum distances and the parents from which the path
//can be recreated.
struct distanceParent{
    vector<int> distance;
    vector<int> parent;
};

//Input
//Two inputs, an adjacency list G and an integer for the index of the starting 
//node. G is a vector the size of the number of nodes.
//Each element is a vector contatining a pair for each edge going from the node.
//The pairs consist of an integer for the index of the connecting node and the 
//weight, meaning the cost of the connection.
// 
//Exceptions:
//The weights can't be negative because if a negative cycle is created the 
//algorithm will not terminate.
//
//Output
//the function returns a struct consisting of two vectors. The first, a vector 
//that for each node contains the distance from the the source to the node.
//The second, a vector that for each node contains the precious node to enable
//the shortest path to be derived.
struct distanceParent shortest_path(vector<vector<pair<int,int>>> G, int start){
    int n = G.size();
    vector<int> dist(n,INT_MAX);
    vector<int> prev(n, -1);
    vector<bool> bIncluded(n, false);
    dist[start] = 0;
    //A set is used as a que to implement dijkstras algorithm more time efficient.
    //The que starts with the starting node and replaces it with all the nodes
    //that can be reached from that node. When a new node is selected it will be
    //the one with the shortest distance since elements in a set is sorted.
    //The shortest path have been found for the node being selected assuming 
    //there are no negative weights. For each node it checks if using its 
    //connection can lead to a shorter path to the node the connection connects. 
    set<pair<int,int>> que;
    que.insert({0, start});
    while(!que.empty()){
        int curNode = que.begin()->second;
        que.erase(que.begin());
        for (auto edge : G[curNode]) {
            int to = edge.first;
            int len = edge.second;
            if (dist[curNode] + len < dist[to]) {
                //the node and its distance is erased and replaced with the new
                //distance
                que.erase({dist[to],to});
                dist[to] = dist[curNode] + len;
                prev[to] = curNode;
                que.insert({dist[to],to});
            }
        }
    }
    struct distanceParent distPar;
    distPar.distance = dist;
    distPar.parent = prev;
    return distPar;
}


//Input:
//The input consists of several test cases terminated with a line of 
//contatining four zeros.
//Each test case starts with a 
//line with four non-negative integers, 1≤n≤10000, 0≤m≤30000, 1≤q≤100 and
//0≤s<n, separated by single spaces, where n is the numbers of nodes in the
//graph, m the number of edges, q the number of queries and s the index of 
//the starting node. Nodes are numbered from 0 to n−1. Then follow m lines,
//each line consisting of three (space-separated) integers u, v and w 
//indicating that there is an edge from u to v in the graph with weight 
//0≤w≤1000. Then follow q lines of queries, each consisting of a single 
//non-negative integer, asking for the minimum distance from node s to the
//node number given on the query line.
//
//Output:
//For each query, a single line containing the minimum distance from node s
//to the node specified in the query is outputed, or the word “Impossible”
//if there is not path from s to that node. Between each test case a blank 
//line is outputted.
//
int main(){
    while(true){
        int n, m, q, start;
        int node1, node2, weight;
        int endNode;
        vector<int> dist;
        vector<int> parent;
        struct distanceParent distPar; 
        //Input   
        scanf("%d", &n);
        scanf("%d", &m);
        scanf("%d", &q);
        scanf("%d", &start);
        vector<int> endPoints(q); 
        //If terminate line detected
        if ((n == 0) && (m == 0) && (q == 0) && (start == 0)){
            break;
        }
        //Creating the skeleton for the adjacency list
        vector<vector<pair<int,int>>> G;
        vector<pair<int,int>> pairVect;
        for (int i = 0; i<n;i++){
            G.push_back(pairVect);
        }
        //Adding input to the adjacency list
        for (int i = 0; i < m; i++){
            scanf("%d", &node1);
            scanf("%d", &node2);
            scanf("%d", &weight);
            G[node1].push_back(make_pair(node2,weight)); 
        }
        //Inputing queries
        for (int i = 0; i< q; i++){
            scanf("%d", &endNode);
            endPoints[i] = endNode;

        } 
        distPar = shortest_path(G,start);
        dist = distPar.distance;
        parent = distPar.parent;
        //Output formatting
        for (int i = 0; i < q; i++){
            if (dist[endPoints[i]] == INT_MAX){
                printf("Impossible \n");
            }
            else {
                printf("%d \n" , dist[endPoints[i]]);
            } 
        }
        printf("\n");
    } 
     
    return 0;
}
















