class Solution {
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        vector<set<pair<int, int>>> top3adj(scores.size());

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            top3adj[u].insert({scores[v], v});
            top3adj[v].insert({scores[u], u});
        }

        for (int i = 0; i < scores.size(); i++) {
            while (top3adj[i].size() > 3)
                top3adj[i].erase(top3adj[i].begin());
        }

        int max_score = -1;
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            if (top3adj[u].size() <= 1)
                continue;
            if (top3adj[v].size() <= 1)
                continue;

            max_score = max(max_score, getMaxNeighbors(u, v, top3adj, scores));
        }
        return max_score;
    }

    int getMaxNeighbors(int u, int v, vector<set<pair<int, int>>>& top3adj,
                        vector<int>& scores) {
        int max_score = -1;
        for (auto next_u = top3adj[u].rbegin(); next_u != top3adj[u].rend();
             next_u++) {
            if (next_u->second == v)
                continue;
            for (auto next_v = top3adj[v].rbegin(); next_v != top3adj[v].rend();
                 next_v++) {
                if (next_v->second == u)
                    continue;
                if (next_u->second == next_v->second)
                    continue;
                max_score = max(max_score, next_v->first + next_u->first +
                                               scores[u] + scores[v]);
            }
        }
        return max_score;
    }
};