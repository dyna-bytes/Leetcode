class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());

        int cnt = 1;
        while (pq.size() && cnt < k) {
            pq.pop();
            cnt++;
        }

        return pq.top();
    }
};