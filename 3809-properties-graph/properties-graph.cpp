class Solution {
    int intersect(unordered_set<int>& a, unordered_set<int>& b) {
        int cnt = 0;
        for (auto n: a)
            if (b.count(n)) cnt++;
        return cnt;
    }
    void dfs(int curr, unordered_map<int, int>& visited, vector<vector<int>>& adj) {

        for (int next: adj[curr]) {
            if (visited[next]) continue;
            visited[next] = true;
            dfs(next, visited, adj);
        }
    }
public:
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        int N = properties.size();
        int M = properties[0].size();
        vector<unordered_set<int>> props(N);
        vector<vector<int>> adj(N);

        for (int i = 0; i < N; i++)
            for (int n : properties[i]) props[i].insert(n);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) continue;

                if (intersect(props[i], props[j]) >= k) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        int cnt = 0;
        unordered_map<int, int> visited;
        for (int i = 0; i < N; i++) {
            if (visited[i]) continue;
            visited[i] = true;
            dfs(i, visited, adj);
            cnt++;
        }
        return cnt;
    }
};