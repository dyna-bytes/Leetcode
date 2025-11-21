class Solution {
public:
    void sortColors(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> pq(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            nums[i] = pq.top();
            pq.pop();
        }
    }
};