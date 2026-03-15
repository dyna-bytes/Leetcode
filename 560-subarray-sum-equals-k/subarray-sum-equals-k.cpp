class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + nums[i];

        int ret = 0;
        for (int e = 0; e <= n; e++) {
            for (int s = 0; s < e; s++) {
                if (pref[e] - pref[s] == k)
                    ret++;
            }
        }
        return ret;
    }
};