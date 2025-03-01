class Solution {
public:
    typedef long long ll;
    vector<vector<int>> adj;
    vector<int> visited;

    int dfs(int curr) {
        int cnt = 1;
        visited[curr] = true;

        for (int next: adj[curr]){
            if (visited[next]) continue;

            cnt += dfs(next);
        }

        return cnt;
    }

    ll dist_square(vector<int>& a, vector<int>& b) {
        return ((ll)a[0] - (ll)b[0])*((ll)a[0] - (ll)b[0]) + 
                ((ll)a[1] - (ll)b[1])*((ll)a[1] - (ll)b[1]);
    }

    void try_merge(int a, int b, vector<vector<int>>& bombs) {
        auto prev = bombs[a];
        auto curr = bombs[b];

        ll dist = dist_square(prev, curr);
        
        if (dist <= (ll)prev[2]*prev[2]) 
            adj[a].push_back(b);
        if (dist <= (ll)curr[2]*curr[2])
            adj[b].push_back(a);
    };

    int maximumDetonation(vector<vector<int>>& bombs) {
        sort(bombs.begin(), bombs.end());
        adj.resize(bombs.size());
        visited.resize(bombs.size(), false);

        for (int i = 0; i < bombs.size(); i++)
            for (int j = 0; j < bombs.size(); j++)
                if (i != j) try_merge(i, j, bombs);
        
        int max_detonation = 0;
        for (int i = 0; i < bombs.size(); i++) { 
            fill(visited.begin(), visited.end(), false);

            max_detonation = max(max_detonation, 
                dfs(i));
        }
        return max_detonation;
    }
};