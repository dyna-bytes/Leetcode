class Solution {
    typedef pair<int, int> pii;
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, vector<int>> adj;
        vector<int> visited(n, 0);
        queue<pii> q;

        for (int i = 0; i < n; i++) 
            adj[arr[i]].push_back(i);

        auto inRange = [&](int idx) {
            return 0 <= idx && idx < n;
        };

        q.push({0, 0});
        visited[0] = true;
        while (q.size()) {
            auto [idx, step] = q.front(); q.pop();

            if (idx == n-1) return step;

            if (inRange(idx + 1) && !visited[idx + 1]) {
                visited[idx + 1] = true;
                q.push({idx + 1, step + 1});
            }
            if (inRange(idx - 1) && !visited[idx - 1]) {
                visited[idx - 1] = true;
                q.push({idx - 1, step + 1});
            }
            for (int nxt: adj[arr[idx]]) {
                if (visited[nxt]) continue;
                visited[nxt] = true;
                q.push({nxt, step + 1});
            }
            adj.erase(arr[idx]);
        }
        return -1;
    }
};