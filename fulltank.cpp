#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

struct Edge {
    int to, length;
};

struct State {
    int cost, city, fuel;

    bool operator>(const State &other) const {
        return cost > other.cost;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> fuel_price(n);
    for (int i = 0; i < n; ++i) {
        cin >> fuel_price[i];
    }

    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].push_back({v, d});
        graph[v].push_back({u, d});
    }

    int q;
    cin >> q;
    while (q--) {
        int capacity, start, end;
        cin >> capacity >> start >> end;

        vector<vector<int>> dist(n, vector<int>(capacity + 1, numeric_limits<int>::max()));
        priority_queue<State, vector<State>, greater<State>> pq;

        dist[start][0] = 0;
        pq.push({0, start, 0});

        while (!pq.empty()) {
            State current = pq.top();
            pq.pop();

            int current_cost = current.cost;
            int current_city = current.city;
            int current_fuel = current.fuel;

            if (current_city == end) {
                cout << current_cost << endl;
                break;
            }

            if (current_cost > dist[current_city][current_fuel]) {
                continue;
            }

            // Refuel at the current city
            if (current_fuel < capacity) {
                int new_cost = current_cost + fuel_price[current_city];
                int new_fuel = current_fuel + 1;
                if (new_cost < dist[current_city][new_fuel]) {
                    dist[current_city][new_fuel] = new_cost;
                    pq.push({new_cost, current_city, new_fuel});
                }
            }

            // Travel to neighboring cities
            for (const auto &edge : graph[current_city]) {
                if (current_fuel >= edge.length) {
                    int new_city = edge.to;
                    int new_fuel = current_fuel - edge.length;
                    if (current_cost < dist[new_city][new_fuel]) {
                        dist[new_city][new_fuel] = current_cost;
                        pq.push({current_cost, new_city, new_fuel});
                    }
                }
            }
        }

        if (dist[end][0] == numeric_limits<int>::max()) {
            cout << "impossible" << endl;
        }
    }

    return 0;
}
