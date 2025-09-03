#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl;\
} while(0)

class Solution {
    typedef pair<int, int> pii;
    const int INF = 1e9;
    vector<vector<pii>> adj;

    int dijstra(vector<vector<int>>& edges, int maxMoves, int n) {
        vector<int> dist(n, INF);
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        dist[0] = 0;
        pq.push({ 0, 0 });

        while (!pq.empty()) {
            auto [dist_curr, curr] = pq.top(); pq.pop();

            if (dist_curr > dist[curr]) continue;

            for (auto& [next, cost]: adj[curr]) {
                if (dist[next] <= dist[curr] + cost) continue;
                dist[next] = dist[curr] + cost;
                pq.push({ dist[next], next });
            }
        }

        int reachables = 0;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++) 
            if (dist[i] <= maxMoves) {
                reachables++;
                visited[i] = true;
            }

        for (vector<int>& edge: edges) {
            int u = edge[0], v = edge[1], cnt = edge[2];
            reachables += min(cnt,
                max(maxMoves - dist[u], 0) + 
                max(maxMoves - dist[v], 0));
        }

        return reachables;
    }
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        if (edges.size() == 0)
            return (maxMoves >= 1);
        
        adj.resize(n);
        for (vector<int>& edge: edges) {
            int u = edge[0], v = edge[1], cnt = edge[2];
            adj[u].push_back({ v, cnt + 1 });
            adj[v].push_back({ u, cnt + 1 });
        }

        return dijstra(edges, maxMoves, n);
    }
};