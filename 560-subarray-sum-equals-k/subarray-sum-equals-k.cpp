class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> sums;
        int sum = 0, ret = 0;
        sums[0] = 1;
        for (int n: nums) {
            sum += n;
            if (sums.count(sum - k))
                ret += sums[sum - k];

            sums[sum]++;
        }
        return ret;
    }
};