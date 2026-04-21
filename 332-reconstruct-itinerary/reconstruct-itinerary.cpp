class Solution {
    map<string, multiset<string>> adj;

    void dfs(const string& curr, vector<string>& ret) {
        while (adj[curr].size()) {
            string next = *adj[curr].begin();
            adj[curr].erase(adj[curr].begin());

            dfs(next, ret);
        }
        ret.push_back(curr);
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto& ticket: tickets) {
            string& from = ticket[0];
            string& to = ticket[1];
            adj[from].insert(to);
        }

        vector<string> ret;
        dfs("JFK", ret);
        reverse(ret.begin(), ret.end());
        return ret;
    }
};