class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret;

        for (int i = 0; i < n; i++) {
            int v = abs(nums[i]);
            nums[v-1] = -abs(nums[v-1]);
        }

        for (int i = 0; i < n; i++) {
            if (nums[i] > 0)
                ret.push_back(i + 1);
        }

        return ret;
    }
};