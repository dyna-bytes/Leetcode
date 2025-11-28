class Solution {
    int n, k;
    vector<vector<int>> adj;
    vector<int> values;
    vector<int> visited;

    int split = 0;

    int f(int curr) {
        int sum = values[curr];

        for (int next: adj[curr]) {
            if (visited[next]) continue;
            visited[next] = true;
            sum += f(next);
        }

        sum %= k;
        if (sum == 0) split++;
        return sum;
    }
public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        adj.resize(n);
        for (auto& edge: edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        this->n = n;
        this->k = k;
        this->values = values;
        visited.resize(n, 0);

        visited[0] = true;
        int ret = f(0);
        return split;
    }
};