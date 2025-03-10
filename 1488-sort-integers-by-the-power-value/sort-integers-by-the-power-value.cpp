class Solution {
public:
    unordered_map<int, int> dp;
    int getPower(int n) {
        if (n == 1) return 1;

        int& ret = dp[n];
        if (ret) return ret;

        ret = 1;
        if (n & 1)
            ret += getPower(3*n+1);
        else
            ret += getPower(n/2);
        return ret;
    }

    int getKth(int lo, int hi, int k) {
        vector<pair<int, int>> powers(hi-lo+1);
        for (int x = lo; x <= hi; x++)
            powers[x-lo] = {getPower(x), x};

        sort(powers.begin(), powers.end());
        return powers[k-1].second;
    }
};