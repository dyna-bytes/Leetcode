class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0) return 0;
        int N = nums.size();
        int k = 0;
        
        int p = 0;
        for (int i = 0; i < N; i++) {
            if (nums[i] != val) {
                swap(nums[p], nums[i]);
                p++;
            }
        }

        nums.erase(nums.begin() + p, nums.end());
        return nums.size();
    }
};
