#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    const int K = 5000;
    int N;
    vector<vector<int>> dp;
    int f(int curr, int diff, vector<int>& rods) {
        if (curr >= N) 
            return (diff == 0) ? 0 : INT_MIN;
        
        int& ret = dp[curr][diff + K];
        if (ret != -1) return ret;

        ret = f(curr + 1, diff, rods);
        ret = max(ret, rods[curr] + f(curr + 1, diff + rods[curr], rods));
        ret = max(ret, f(curr + 1, diff - rods[curr], rods));
        return ret;
    }
public:
    int tallestBillboard(vector<int>& rods) {
        N = rods.size();
        dp.resize(N + 1, vector<int>(2 * K, -1));
        return f(0, 0, rods);
    }
};