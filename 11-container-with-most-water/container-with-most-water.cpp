class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = 0;
        for (int i = 0, j = height.size() - 1; i < j; ) {
            int area = (j - i) * min(height[i], height[j]);
            maxArea = max(maxArea, area);
            if (height[i] == min(height[i], height[j])) i++;
            else j--;
        }
        return maxArea;
    }
};