class Solution {
    int n;
    typedef pair<int, int> pii;
    const int INF = 1e9 + 1;

    int dijkstra(vector<vector<pii>>& adj) {
        vector<int> dist(n, INF);
        vector<int> visited(n, false);
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        dist[0] = 0;
        pq.push({dist[0], 0});

        while (pq.size()) {
            auto [d, curr] = pq.top(); pq.pop();

            if (visited[curr]) continue;
            visited[curr] = true;

            for (auto& [next, weight]: adj[curr]) {
                if (dist[next] <= d + weight) continue;
                
                dist[next] = d + weight;
                pq.push({dist[next], next});
            }
        }

        return (dist[n -1] >= INF) ? -1 : dist[n - 1];
    }
public:
    int minCost(int n, vector<vector<int>>& edges) {
        this->n = n;
        vector<vector<pii>> adj(n);
        for (auto& edge: edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, 2*w});
        }

        return dijkstra(adj);
    }
};