class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        unordered_map<int, int> hashmap;

        for (int i = 0; i < n; i++) {
            int target = nums[i];

            for (int j = i + 1, k = n - 1; j < k; ) {
                int eq = target + nums[j] + nums[k];
                if (eq < 0) j++;
                else if (eq > 0) k--;
                else if (hashmap.count(nums[j]) && hashmap[nums[j]] == nums[i]) j++, k--;
                else {
                    ans.push_back({nums[i], nums[j], nums[k]});
                    hashmap[nums[j]] = nums[i];
                    j++, k--;
                }
            }
        }
        return ans;
    }
};