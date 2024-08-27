#include<bits/stdc++.h>
using namespace std;

void print2dVector(vector<vector<int>> vect){
    //cout << "print" << endl;
    for (int i = 0; i< vect.size(); i++){
        //cout << i << endl;
        cout << vect.size();
        for (int j=0; j < vect[i].size(); j++){
            //cout << "i " << i << " j " << j << " " <<  vect[i][j] << endl;
            int x = 0; 
        }
    }
}


void print2dVectorPair(vector<vector<pair<int,float>>> vect){
    //cout << "print" << endl;
    for (int i = 0; i< vect.size(); i++){
        //cout << i << endl;
        //cout << vect.size();
        for (int j=0; j < vect[i].size(); j++){
            cout << "i " << i << " j " << j << " " <<  vect[i][j].first << " " << vect[i][j].second<< endl;
            //int x = 0; 
        }
    }
}

struct distanceParent{
    vector<float> distance;
    vector<int> parent;
};

struct distanceParent shortest_path(vector<vector<pair<int,float>>> G, int start){
    //print2dVectorPair(G);
    int n = G.size();
    vector<float> dist(n,0);
    vector<int> prev(n, -1);
    vector<bool> bIncluded(n, false);
    dist[start] = 1;
    //A set is used as a que to implement dijkstras algorithm more time efficient.
    //The que starts with the starting node and replaces it with all the nodes
    //that can be reached from that node. When a new node is selected it will be
    //the one with the lowest distance since elements in a set is sorted.
    set<pair<float,int>> que;
    set<pair<float,int>>::iterator it;
    set<pair<float,int>>::reverse_iterator rit;
    que.insert({1.0, start});
    while(!que.empty()){
        rit = que.rbegin();
        auto temp = *rit;
        int curNode = temp.second;
        //it = --que.end();
        //pair<float,int> temp = que.rbegin();
        //int curNode = *que.rbegin()->second;
        //cout << curNode;
        que.erase(*rit); 
        //que.erase(it);
        //cout << que.size() << " " << curNode <<endl;
        //que.erase(que.end());
        for (auto edge : G[curNode]) {
            int to = edge.first;
            float len = edge.second;
            if (dist[curNode] * len > dist[to]) {
                que.erase({dist[to],to});
                dist[to] = dist[curNode] * len;
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

/*
vector<float> dijkstra(int start, vector<vector<float>> adj) {
    int n = adj.size();
    vector<float> dist(n,0);
    vector<int> prev(n, -1);
    vector<bool> bIncluded(n, false);
    dist[start] = 1;

    for (int i = 0; i < n-1; i++) {
        int curNode = -1;
        for (int j = 0; j < n; j++) {
            if (!bIncluded[j] && (curNode == -1 || dist[j] > dist[curNode]))
                curNode = j;
        }
        if (dist[curNode] == 0)
            break;
        bIncluded[curNode] = true;
        for (int j = 0; j<n; j++){
            if (!bIncluded[j] && adj[curNode][j] > 0 && dist[curNode] > 0 && 
                dist[curNode] * adj[curNode][j] > dist[j]){
                dist[j] = dist[curNode] * adj[curNode][j];
            }
        }
    }
    return dist;
}
*/

int main() {
    int n, m;
    int node1,node2;
    float weight;
    vector<float> dist;
    while(true){
        scanf("%d", &n);
        scanf("%d", &m);
        if ((n == 0) && (m==0)){
           break;
        }

        //vector<vector<float>> adj(n, vector<float> (n,0));
         
        vector<vector<pair<int,float>>> G;
        vector<pair<int,float>> pairVect;
        for (int i = 0; i<n;i++){
            G.push_back(pairVect);
        }
        for (int i = 0; i < m; i++){
            scanf("%d", &node1);
            scanf("%d", &node2);
            scanf("%f", &weight);
            //adj[node1][node2] = weight;
            //adj[node2][node1] = weight;
            G[node1].push_back(make_pair(node2,weight)); 
            G[node2].push_back(make_pair(node1,weight));
        }
        struct distanceParent distPar;
        distPar = shortest_path(G,0);
        dist = distPar.distance;
        //dist = dijkstra(0, adj);
        printf("%.4f \n" , dist[n-1]);
        }        
    return 0;

}
