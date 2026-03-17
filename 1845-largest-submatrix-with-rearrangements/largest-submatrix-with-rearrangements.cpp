class Solution {
    // [s, e)
    int findMax(int s, int e, vector<int>& heights) {
        if (s >= e) return 0;
        else if (s + 1 == e) return heights[s];

        int m = (s + e)/2;
        int l = m, r = m;
        int max_h = heights[m];
        int max_area = heights[m] * 1;

        while (s < l || r + 1 < e) {
            int p = (s < l) ? heights[l - 1] : -1;
            int q = (r + 1 < e) ? heights[r + 1] : -1;

            if (p >= q) {
                max_h = min(max_h, p);
                l--;
            } else {
                max_h = min(max_h, q);
                r++;
            }

            max_area = max(max_area, max_h * (r - l + 1));
        }

        return max({max_area, findMax(s, m, heights), 
            findMax(m, e, heights)});
    }
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int Y = matrix.size(), X = matrix[0].size();
        vector<int> heights(X, 0);

        int ret = 0;
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                if (matrix[y][x]) heights[x]++;
                else heights[x] = 0;
            }

            vector<int> copy = heights;
            sort(copy.begin(), copy.end());
            ret = max(ret, findMax(0, X, copy));
        }
        return ret;
    }
};