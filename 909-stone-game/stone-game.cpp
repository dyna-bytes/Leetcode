class Solution {
    vector<int> piles;
    vector<vector<int>> dp;

    // 구간 [l, r]에서, 현재 턴인 플레이어와 상대방 사이의 최대 점수 차이
    int f(int l, int r) {
        if (l == r) return piles[l];

        int& ret = dp[l][r];
        if (ret != -1) return ret;
        return ret = max(piles[l] - f(l+1, r), piles[r] - f(l, r-1));
    }
public:
    bool stoneGame(vector<int>& piles) {
        this->piles = piles;
        int n = piles.size();
        dp.assign(n, vector<int>(n, -1));

        return f(0, n-1) > 0;
    }
};