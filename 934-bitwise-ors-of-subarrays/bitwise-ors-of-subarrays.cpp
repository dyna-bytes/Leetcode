class Solution {
    int N;
    unordered_map<int, unordered_set<int>> dp;
    unordered_set<int>& f(int curr, vector<int>& arr) {
        if (curr >= N) {
            return dp[curr];
        }

        if (dp.count(curr)) return dp[curr];
        unordered_set<int>& ret = dp[curr];
        unordered_set<int>& prev_ors = f(curr + 1, arr);
        
        ret.insert(arr[curr]);
        for (auto p_or: prev_ors)
            ret.insert(p_or | arr[curr]);

        return ret;
    }
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        N = arr.size();
        unordered_set<int> total_ors;

        for (int i = 0; i < N; i++) {
            auto& ors = f(i, arr);
            total_ors.insert(ors.begin(), ors.end());
        }
        return total_ors.size();
    }
};