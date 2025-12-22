class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int Y = strs.size();
        int X = strs[0].size();
        vector<int> dp(X, 1);

        for (int x = 1; x < X; x++) {
            int max_dp = 0;
            for (int k = x - 1; k >= 0; k--) {
                bool pass = true;
                for (int y = 0; y < Y; y++) {
                    if (strs[y][k] > strs[y][x]) {
                        pass = false;
                        break;
                    }
                }

                if (pass)
                    max_dp = max(max_dp, dp[k]);
            }

            dp[x] = max_dp + 1;
        }

        return X - *max_element(dp.begin(), dp.end());
    }
};