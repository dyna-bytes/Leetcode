class Solution {
    typedef long long ll;
    const ll MOD = 1e9 + 7;
    unordered_map<int, vector<int>> adj;
    unordered_map<int, int> visited;
    int dfs(int curr) {
        int ret = 0;
        for (int next: adj[curr]) {
            if (visited[next]) continue;
            visited[next] = true;
            ret = max(ret, dfs(next));
        }
        return ret + 1;
    }
    ll pow(int n, int k) {
        if (k == 0) return 1;
        if (k == 1) return n;
        if (k % 2 == 1) return pow(n, k/2) * pow(n, k/2) * n % MOD;
        return pow(n, k/2) * pow(n, k/2) % MOD;
    }
public:
    int assignEdgeWeights(vector<vector<int>>& edges) {
        for (vector<int>& edge: edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        visited[1] = true;
        int depth = dfs(1) - 1;

        return pow(2, depth - 1);
    }
};