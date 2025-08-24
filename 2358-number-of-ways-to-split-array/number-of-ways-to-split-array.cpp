class Solution {
    typedef long long ll;
public:
    int waysToSplitArray(vector<int>& nums) {
        int n = nums.size();
        vector<ll> pref(n+1, 0); // pref[i] : sum(nums[0, i))
        // pref[a] - pref[b] = sum(nums[b, a))
        for (int i = 0; i < n; i++)
            pref[i+1] = pref[i] + nums[i];

        int cnt = 0;
        for (int i = 0; i < n - 1; i++) 
            if (pref[n] - pref[i + 1] <= pref[i + 1]) 
                cnt++;
        
        return cnt;
    }
};