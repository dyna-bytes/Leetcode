class Solution {
    typedef pair<int, int> pii;
    deque<pii> dq; // monotone decreasing queue, 
    // so the first value is the largest value for previous ranges.
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ret(n - k + 1);

        for (int i = 0; i < n; i++) {
            while (!dq.empty() && dq.front().second < i - k + 1)
                dq.pop_front();

            while (!dq.empty() && dq.back().first <= nums[i])
                dq.pop_back();

            dq.push_back({ nums[i], i });
            if (i >= k - 1)
                ret[i - k + 1] = dq.front().first;
        }
        return ret;
    }
};