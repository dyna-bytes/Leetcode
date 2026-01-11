class Solution {
    vector<int> heights;
    int findMax(int s, int e) { // [s, e)
        if (s >= e) return 0;
        if (s + 1 == e) return heights[s];

        int m = (s + e) / 2;
        int left = findMax(s, m);
        int right = findMax(m, e);

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
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        this->heights = heights;

        return findMax(0, n);
    }
};