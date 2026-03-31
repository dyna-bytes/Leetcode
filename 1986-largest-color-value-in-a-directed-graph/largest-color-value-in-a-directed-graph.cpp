class Solution {
    const int UNVISITED = 0;
    const int VISITING = 1;
    const int VISITED = 2;
    string colors;
    vector<vector<int>> adj;
    vector<int> visited;
    vector<vector<int>> dp;

    int dfs(int curr) {
        if (visited[curr] == VISITING) return -1;
        if (visited[curr] == VISITED) return 0; 
        visited[curr] = VISITING;

        for (int next: adj[curr]) {
            if (dfs(next) == -1) return -1;

            for (int i = 0; i < 26; i++)
                dp[curr][i] = max(dp[next][i], dp[curr][i]);
        }

        visited[curr] = VISITED;
        dp[curr][colors[curr] - 'a']++;

        return 0;
    }
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        this->colors = colors;
        int n = colors.size();
        adj.resize(n);
        visited.resize(n, false);
        dp.resize(n, vector<int>(26, 0));

        for (auto& edge: edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
        }

        for (int i = 0; i < n; i++) {
            if (visited[i] == UNVISITED)
                if (dfs(i) == -1) return -1;
        }

        int ret = 0;
        for (vector<int>& d: dp)
            for (int v: d) ret = max(v, ret);
        return ret;
    }
};