class Solution {
    int findMax(int s, int e, vector<int>& heights) { // [s, e)
        if (s >= e) return 0;
        if (s + 1 == e) return heights[s];

        int m = (s + e) / 2;
        int left = findMax(s, m, heights);
        int right = findMax(m, e, heights);

        int max_h = heights[m];
        int max_area = heights[m];
        int l = m;
        int r = m;
        while (s < l || r < e - 1) {
            int p = (s < l) ? heights[l - 1] : -1;
            int q = (r < e - 1) ? heights[r + 1] : -1;

            if (p >= q) {
                max_h = min(max_h, p);
                l--;
            } else {
                max_h = min(max_h, q);
                r++;
            }
            max_area = max(max_area, max_h * (r - l + 1));
        }

        return max({left, right, max_area});
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int Y = matrix.size();
        int X = matrix[0].size();

        vector<int> heights(X, 0);

        int ret = 0;
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                if (matrix[y][x] == '0') heights[x] = 0;
                else heights[x]++;
            }
            ret = max(ret, findMax(0, X, heights));
        }
        return ret;
    }
};