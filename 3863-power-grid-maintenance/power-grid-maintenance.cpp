class Solution {
    typedef pair<int, int> pii;
    vector<set<int>> adj;
    vector<int> visited;
    vector<set<int>> onlines;
    unordered_map<int, int> group;

    void bfs(int start, set<int>& online, int group_num) {
        queue<int> q;

        q.push(start);
        visited[start] = true;

        while (q.size()) {
            int curr = q.front(); q.pop();
            online.insert(curr);
            group[curr] = group_num;

            for (int next: adj[curr]) {
                if (visited[next]) continue;
                visited[next] = true;
                q.push(next);
            }
        }
    }
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        adj.resize(c+1);
        visited.resize(c+1, false);

        for (auto& connection: connections) {
            int u = connection[0], v = connection[1];
            adj[u].insert(v);
            adj[v].insert(u);
        }

        int group_num = 0;
        for (int i = 1; i <= c; i++) {
            if (visited[i]) continue;
            onlines.push_back(set<int>{});
            bfs(i, onlines.back(), group_num++);
        }

        vector<int> ans;
        for (auto& query: queries) {
            int op = query[0], x = query[1];
            auto& online = onlines[group[x]];
            if (op == 1) {
                if (online.count(x)) ans.push_back(x);
                else if (online.size()) ans.push_back(*online.begin());
                else ans.push_back(-1);
            } else {
                online.erase(x);
            }
        }
        return ans;
    }
};