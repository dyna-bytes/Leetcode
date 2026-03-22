class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_area = 0;
        int l = 0;
        int r = height.size() - 1;

        while (l < r) {
            int current_area = min(height[l], height[r]) * (r - l);
            max_area = max(max_area, current_area);

            if (height[l] < height[r]) {
                l++;
            } else {
                r--;
            }
        }

        return max_area;
    }
};