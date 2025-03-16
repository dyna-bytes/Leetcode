class Solution {
    unordered_map<string,
                  priority_queue<string, vector<string>, greater<string>>>
        adj;
    void dfs(const string& curr, vector<string>& ret) {
        while (!adj[curr].empty()) {
            string next = adj[curr].top();
            adj[curr].pop();
            dfs(next, ret);
        }
        ret.push_back(curr); 
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto& ticket : tickets) {
            string& from = ticket[0];
            string& to = ticket[1];
            adj[from].push(to);
        }
        vector<string> ret;
        dfs("JFK", ret);
        reverse(ret.begin(), ret.end());
        return ret;
    }
};