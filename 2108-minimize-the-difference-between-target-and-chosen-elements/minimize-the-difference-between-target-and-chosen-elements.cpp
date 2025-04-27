class Solution {
    int Y, X;
    vector<vector<int>> dp;

    int f(int y, int sum, vector<vector<int>>& mat, int target) {
        if (y == Y) 
            return abs(sum - target);
        
        int& minDiff = dp[y][sum];
        if (minDiff != -1) return minDiff;

        minDiff = INT_MAX;
        for (int x = 0; x < X; x++)
            minDiff = min(minDiff, f(y+1, sum + mat[y][x], mat, target));
        return minDiff;
    }
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        Y = mat.size(), X = mat[0].size();
        int S = 0;
        for (vector<int>& row: mat)
            for (auto& n: row)
                S += n;
        
        dp.resize(Y, vector<int>(S, -1));
        return f(0, 0, mat, target);
    }
};