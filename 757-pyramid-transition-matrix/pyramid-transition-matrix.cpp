class Solution {
    unordered_map<string, bool> dp;
    unordered_map<string, vector<char>> allowedset;
    bool f(int i, const string& bottom, const string& top) {
        if (bottom.size() <= 1) return true;

        if (i + 1 == bottom.size())
            return f(0, top, "");

        if (i == 0 && dp.count(bottom))
            return dp[bottom];

        string curr = bottom.substr(i, 2);
        bool ret = false;
        for (char allowed: allowedset[curr])
            ret += f(i + 1, bottom, top + allowed);
        return dp[bottom] = ret;
    }
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for (auto& str: allowed) 
            allowedset[str.substr(0, 2)].push_back(str[2]);
        return f(0, bottom, "");
    }
};