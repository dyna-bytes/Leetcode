class Solution {
    int n;
    vector<int> nums;
    vector<int> arr;
public:
    Solution(vector<int>& nums) {
        n = nums.size();
        this->nums = nums;
        this->arr = nums;
    }
    
    vector<int> reset() {
        return nums;
    }
    
    vector<int> shuffle() {
        arr = nums;
        for (int i = 1; i < n; i++) {
            int j = rand() % (i + 1); // 0 <= j <= i;
            swap(arr[i], arr[j]);
        }
        return arr;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */