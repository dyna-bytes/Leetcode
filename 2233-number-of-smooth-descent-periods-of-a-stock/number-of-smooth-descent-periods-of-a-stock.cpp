class Solution {
    typedef long long ll;
public:
    long long getDescentPeriods(vector<int>& prices) {
        int n = prices.size();
        ll ret = 0;
        
        int e = 0;
        for (int s = 0; s < n; s++) {
            for (e = s + 1; e < n && prices[e] == prices[e - 1] - 1; e++) ;

            ll k = e - s;
            ret += k * (k + 1) / 2;
            s = e - 1;
        }
        return ret;
    }
};