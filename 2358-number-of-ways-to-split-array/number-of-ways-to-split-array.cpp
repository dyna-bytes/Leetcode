class Solution {
    typedef long long ll;
public:
    int waysToSplitArray(vector<int>& nums) {
        int n = nums.size();
        vector<ll> prefix(n+1, 0);
        for (int i = 0; i < n; i++)
            prefix[i+1] = prefix[i] + nums[i];

        int valid = 0;
        for (int i = 0; i < n-1; i++)
            if (prefix[i+1] >= prefix[n] - prefix[i+1]) valid++;
        return valid;
    }
};