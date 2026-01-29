class Solution {
    typedef long long ll;
    typedef pair<ll, ll> pll;
    const ll INF = 1e9;

    vector<vector<ll>> mp;
    vector<vector<pll>> adj;

    void bfs(char start) {
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        mp[start][start] = 0;
        pq.push({ 0, start });

        while (pq.size()) {
            auto [dist, curr] = pq.top(); pq.pop();

            if (mp[start][curr] < dist) continue;

            for (auto& [next, cost]: adj[curr]) {
                if (mp[start][next] <= cost + dist) continue;
                mp[start][next] = cost + dist;
                pq.push({ cost + dist, next });
            }
        }
    }
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        if (source.size() != target.size()) return -1;
        mp.resize('z' + 1, vector<ll>('z' + 1, INF));
        adj.resize('z' + 1);
        
        for (int i = 0; i < original.size(); i++) 
            adj[original[i]].push_back({ changed[i], cost[i] });
        
        for (int i = 'a'; i <= 'z'; i++) 
            bfs(i);

        ll ret = 0;
        for (int i = 0; i < source.size(); i++) {
            int cst = mp[source[i]][target[i]];
            if (cst >= INF) return -1;
            ret += cst;
        }
        return ret;
    }
};