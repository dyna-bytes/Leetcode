#define debug(x) cout << #x << " is " << x << endl;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        unordered_map<int, int> um;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            int target = nums[i];

            for (int j = i + 1, k = nums.size() - 1; j < k; ) {
                int twoSum = nums[j] + nums[k];
                if (twoSum + target > 0) k--;
                else if (twoSum + target < 0) j++;
                else if (um.find(nums[j]) != um.end() && um.find(nums[j])->second == nums[i]) j++, k--;
                else {
                    ret.push_back({nums[i], nums[j], nums[k]});
                    um[nums[j]] = nums[i];
                    j++, k--;
                }
            }
        }
        return ret;
    }
};