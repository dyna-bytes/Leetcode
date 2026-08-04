class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int mn = *min_element(nums.begin(), nums.end());
        int mx = *max_element(nums.begin(), nums.end());

        unordered_set<int> us(nums.begin(), nums.end());
        vector<int> ans;
        for (int i = mn; i <= mx; i++) {
            if (!us.count(i)) ans.push_back(i);
        }
        return ans;
    }
};