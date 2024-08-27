//Author: Axel Ahlqvist
//Problem: Single source shortest path, negative weights
//Finding the shortest path in a graph where negative weights and cycles occur.
//Algorithm: Bellman-Ford
//Time complexity: O(m*n)) 
//Memory complexity(m+n)
#include<bits/stdc++.h>
using namespace std;



//Struct to give both the minimum distances and the parents from which the path
//can be recreated.
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
struct distanceParent{
    vector<int> distance;
    vector<int> parent;
};
struct graph{
    vector<tuple<int,int,int>> edgeList;
    int nNodes;
};
struct distanceParent shortest_path(struct graph G,int start){
    int INF = 10000000;
    int n = G.nNodes;
    int m = G.edgeList.size();
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    vector<int> p (n, -1);
    vector<bool> inNLoop(n,false);
    struct distanceParent distPar;
    for (int i=0; i<2*n; ++i)
    {
        for (int j=0; j<m; ++j){
            int node1= get<0>(G.edgeList[j]);
            int node2 = get<1>(G.edgeList[j]);
            int weight = get<2>(G.edgeList[j]);
            int tempDist;
            if (dist[node1] < INF){
                tempDist = max(-INF, dist[node1] + weight);
                if (dist[node2] > tempDist){
                    if (i >= n-1){
                        inNLoop[node2] = true;
                        dist[node2] = -INF;
                        p[node2] = node1;
                    }
                    else { 
                        dist[node2] = tempDist;
                        p[node2] = node1;
                    }
                }
            }
        }
    }
    for (int i = 0; i <n; i++){
        if (inNLoop[i]){
            dist[i] = -INF;
        }
    }
    distPar.distance = dist;
    distPar.parent = p;
    return distPar;
}
int main(){
    while(true){
        int INF = 10000000;
        int n, m, q, start;
        int node1, node2, weight;
        int endNode;
        vector<int> dist;
        vector<int> parent;
        struct graph G;
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
        vector<tuple<int,int,int>> edgeList(m);

        G.nNodes = n;
        //Adding input to the adjacency list
        for (int i = 0; i < m; i++){
            scanf("%d", &node1);
            scanf("%d", &node2);
            scanf("%d", &weight);
        
            edgeList[i] = make_tuple(node1, node2, weight); 
        }
        //Inputing queries
        for (int i = 0; i< q; i++){
            scanf("%d", &endNode);
            endPoints[i] = endNode;

        } 
        G.edgeList = edgeList;
        distPar = shortest_path(G, start);
        //distPar = shortest_path(G,start);
        dist = distPar.distance;
        parent = distPar.parent;
        //Output formatting
        for (int i = 0; i < q; i++){
            if (dist[endPoints[i]] >= INF){
                printf("Impossible\n");
            }
            else if (dist[endPoints[i]] <= -INF){
                printf("-Infinity\n");
            }
            else{
                printf("%d\n" , dist[endPoints[i]]);
            } 
        }
        printf("\n");
    } 
     
    return 0;
}
