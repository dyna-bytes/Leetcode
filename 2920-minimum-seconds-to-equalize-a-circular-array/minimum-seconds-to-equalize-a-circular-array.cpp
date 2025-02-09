class Solution {
public:
    int minimumSeconds(vector<int>& nums) {
        // gap size (nums[i] - nums[i+1])/2 is the time to the gap
        int N = nums.size();
        unordered_map<int, queue<int>> gaps;
        for (int i = 0; i < N; i++)
            gaps[nums[i]].push(i);
        
        int ans = INT_MAX;
        for (auto& [n, gap]: gaps) {
            gap.push(gap.front() + N);

            int seconds = 0;
            while (gap.size() > 1) {
                int curr = gap.front();
                gap.pop();
                int next = gap.front();
                seconds = max(seconds, (next - curr)/2);
            }
            ans = min(ans, seconds);
        }
        return ans;
    }
};