class Solution {
    typedef long long ll;
    typedef pair<ll, ll> pll;
    const ll INF = 1e14;
    vector<int> robot;
    vector<int> factory;
    vector<vector<ll>> dp;
    ll f(int i, int j) { // i-th robot, j-th factory
        if (i == -1) return 0;
        if (j == -1) return INF;

        ll& ret = dp[i][j];
        if (ret != -1) return ret;
        
        ret = f(i, j-1);
        ret = min(ret, abs(robot[i] - factory[j]) + f(i-1, j-1));
        return ret;
    }
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());
        this->robot = robot;    
        for (vector<int>& facts: factory) 
            for (int i = 0; i < facts[1]; i++)
                this->factory.push_back(facts[0]);

        int N = robot.size();
        int M = this->factory.size();
        dp.assign(N+1, vector<ll>(M+1, -1));
        
        return f(N- 1, M - 1);
    }
};