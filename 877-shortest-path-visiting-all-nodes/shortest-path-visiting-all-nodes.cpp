class Solution {
    typedef pair<int, int> pii;
    vector<vector<int>> visited;

public:
    int status_bfs(vector<vector<int>>& adj) {
        queue<pii> q; // {node, visited status}
        for (int i = 0; i < adj.size(); i++) {
            q.push({i, 1 << i}); // visited node n : (1 << n)
            visited[i][1 << i] = true;
        }

        auto visitedAll = [&](int status) {
            return status == ((1 << adj.size()) - 1);
        };

        int step = 0;
        while (!q.empty()) {
            for (int qsize = q.size(); qsize > 0; qsize--) {
                auto [curr, status] = q.front();
                q.pop();
                // cout << "curr " << curr << " " << bitset<8>(status) << endl;
                if (visitedAll(status))
                    return step;

                for (int next : adj[curr]) {
                    if (visited[next][status | (1 << next)])
                        continue;
                    // cout << "next " << next << " " << bitset<8>(status | (1 << next)) << endl;

                    visited[next][status | (1 << next)] = true;
                    q.push({next, status | (1 << next)});
                }
            }
            step++;
        }
        return 0;
    }
    int shortestPathLength(vector<vector<int>>& graph) {
        visited.resize(graph.size() + 1, vector<int>(1 << graph.size()));
        return status_bfs(graph);
    }
};