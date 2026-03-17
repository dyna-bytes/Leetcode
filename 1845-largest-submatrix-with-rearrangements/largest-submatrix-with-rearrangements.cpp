class Solution {
    typedef pair<int, int> pii;
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int Y = matrix.size(), X = matrix[0].size();
        vector<pii> prevHeights;
        int ret = 0;

        for (int y = 0; y < Y; ++y) {
            vector<pii> heights;
            vector<int> seen(X, 0);

            for (auto& [height, x]: prevHeights) {
                if (matrix[y][x]) {
                    heights.push_back({ height + 1, x });
                    seen[x] = true;
                }
            }

            for (int x = 0; x < X; ++x) {
                if (!seen[x] && matrix[y][x]) 
                    heights.push_back({ 1, x });
            }

            for (int i = 0; i < heights.size(); ++i)
                ret = max(ret, heights[i].first * (i + 1));

            prevHeights = heights;
        }

        return ret;
    }
};