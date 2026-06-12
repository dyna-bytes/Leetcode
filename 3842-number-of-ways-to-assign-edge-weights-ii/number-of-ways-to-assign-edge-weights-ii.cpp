class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
    typedef long long ll;
    const ll MOD = 1e9 + 7;
    int n, max_d = 20;
    vector<vector<int>> adj;
    vector<vector<int>> parent;
    vector<int> visited;
    vector<int> depth;
    void dfs(int curr) {
        for (int next: adj[curr]) {
            if (visited[next]) continue;
            visited[next] = curr;
            depth[next] = depth[curr] + 1;
            dfs(next);
        };
    }

    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];

        for (int j = 0; diff; j++) {
            if (diff % 2) u = parent[u][j];
            diff /= 2;
        }

        if (u != v) {
            for (int j = max_d; j >= 0; j--) {
                if (parent[u][j] != parent[v][j]) {
                    u = parent[u][j];
                    v = parent[v][j];
                }
            }
            u = parent[u][0];
        }
        return u;
    }

    ll pow(int n, int k) {
        if (k == 0) return 1;
        ll half = pow(n, k / 2);
        ll res = (half * half) % MOD;
        if (k % 2 == 1) return (res * n) % MOD;
        return res;
    }
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        n = edges.size() + 1;
        adj.assign(n + 1, vector<int>());
        depth.assign(n + 1, 0);
        visited.assign(n + 1, 0);
        parent.assign(n + 1, vector<int>(max_d + 1, 0));

        for (auto& edge: edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        visited[1] = -1;
        dfs(1);

        parent.assign(n + 1, vector<int>(max_d + 1, 0));
        for (int i = 1; i <= n; i++)
            parent[i][0] = max(visited[i], 0);
        for (int j = 1; j <= max_d; j++)
            for (int i = 1; i <= n; i++)
                parent[i][j] = parent[ parent[i][j-1] ][j-1];

        vector<int> ret;
        for (auto& query: queries) {
            int u = query[0], v = query[1];
            int lca = getLCA(u, v);
            int len = depth[u] + depth[v] - 2 * depth[lca];
            if (len == 0) ret.push_back(0);
            else ret.push_back(pow(2, len-1));
        }
        return ret;
    }
};