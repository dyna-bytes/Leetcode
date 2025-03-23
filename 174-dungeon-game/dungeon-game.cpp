class Solution {
    int Y, X;
    vector<vector<int>> dp;
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        Y = dungeon.size();
        X = dungeon[0].size();

        dp.resize(Y, vector<int>(X, INT_MIN));
        return -minHP(0, 0, dungeon) + 1;
    }

    // keep minHP <= 0
    int minHP(int y, int x, vector<vector<int>>& dungeon) {
        if (y > Y-1 || x > X-1) return INT_MIN;
        if (y == Y-1 && x == X-1) return min(0, dungeon[y][x]);

        int& ret = dp[y][x];
        if (ret != INT_MIN) return ret;

        ret = max(minHP(y+1, x, dungeon), minHP(y, x+1, dungeon)) + dungeon[y][x];
        ret = min(0, ret);
        return ret;
    }
};