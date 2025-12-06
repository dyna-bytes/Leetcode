class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        multiset<int, greater<int>> maxset;
        multiset<int> minset;

        int n = nums.size();
        int maxlen = 0;
        maxset.insert(nums[0]);
        minset.insert(nums[0]);
        for (int s = 0, e = 0; s <= e && e < n; ) {
            while (*maxset.begin() - *minset.begin() <= limit && e < n) {
                maxlen = max(maxlen, e - s + 1);
                
                e++;
                if (e >= n) return maxlen;
                maxset.insert(nums[e]);
                minset.insert(nums[e]);
            }

            while (*maxset.begin() - *minset.begin() > limit && s < e) {
                maxset.erase(maxset.find(nums[s]));
                minset.erase(minset.find(nums[s]));
                s++;
            }
        }
        return maxlen;
    }
};