class Solution {
    int n;
    vector<int> s;
    vector<int> dp;
    int f(int i) {
        if (i == n) return 0;

        int& ret = dp[i];
        if (ret != INT_MIN) return ret;
        
        ret = s[i] - f(i + 1);

        if (i + 1 < n)
            ret = max(ret, s[i] + s[i + 1] - f(i + 2));

        if (i + 2 < n)
            ret = max(ret, s[i] + s[i + 1] + s[i + 2] - f(i + 3));
        return ret;
    }
public:
    string stoneGameIII(vector<int>& stoneValue) {
        this->s = stoneValue;
        this->n = stoneValue.size();
        dp.assign(n + 1, INT_MIN);
        int ret = f(0);

        if (ret == 0) return "Tie";
        else if (ret > 0) return "Alice";
        return "Bob";
    }
};