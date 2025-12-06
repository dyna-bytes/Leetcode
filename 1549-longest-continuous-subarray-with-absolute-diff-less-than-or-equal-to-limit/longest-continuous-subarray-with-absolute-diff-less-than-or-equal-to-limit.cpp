class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        deque<int> maxq; // descending
        deque<int> minq; // ascending
        
        int s = 0;
        int e = 0;
        for (; e < n; e++) {
            while (maxq.size() && nums[e] > maxq.back())
                maxq.pop_back();

            while (minq.size() && nums[e] < minq.back())
                minq.pop_back();

            maxq.push_back(nums[e]);
            minq.push_back(nums[e]);

            if (maxq.front() - minq.front() > limit) {
                if (maxq.front() == nums[s]) maxq.pop_front();
                if (minq.front() == nums[s]) minq.pop_front();
                s++;
            }
        }
        return e - s;
    }
};