class Solution {
    typedef pair<int, int> pii;
public:
    int trap(vector<int>& height) {
        stack<int> monotone; // descendig stack
        int n = height.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            while (monotone.size() && height[monotone.top()] < height[i]) {
                int curr_top = monotone.top();
                monotone.pop();
                if (monotone.empty()) break;
                int prev_top = monotone.top();

                int bound_height = min(height[i], height[prev_top]) - height[curr_top]; 
                int dist = i - prev_top - 1;
                ans += (bound_height * dist);
            }
            monotone.push(i);
        }
        return ans;
    }
};