class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0) return 0;
        int N = nums.size();
       
        int p = 0;
        for (int i = 0; i < N; i++) 
            if (nums[i] != val) 
                nums[p++] = nums[i];
        
        // debugVec(nums);
        return p;
    }
};
