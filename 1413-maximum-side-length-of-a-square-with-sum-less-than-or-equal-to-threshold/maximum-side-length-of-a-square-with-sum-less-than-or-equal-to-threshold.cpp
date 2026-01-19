class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int Y = mat.size();
        int X = mat[0].size();

        // Build 2D prefix sum: prefix[i][j] = sum of mat[0..i-1][0..j-1]
        vector<vector<int>> psum(Y + 1, vector<int>(X + 1, 0));
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                psum[y + 1][x + 1] = psum[y][x + 1] + psum[y + 1][x] - psum[y][x] + mat[y][x];

        for (int k = min(Y, X); k > 0; k--)
            for (int y = 0; y + k <= Y; y++)
                for (int x = 0; x + k <= X; x++) {
                    int sum = psum[y + k][x + k] - psum[y][x + k] - psum[y + k][x] + psum[y][x];

                    if (sum <= threshold)
                        return k;
                }

        return 0;
    }
};