class Solution {
public:
    int maximizeGreatness(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        int cnt = 0;
        int next = 0;
        for (int i = 0; i < n; i++) {
            for (; next < n && nums[i] == nums[next]; next++)
                ;
            
            if (next != n) {
                nums[i] = nums[next];
                cnt++;
                next++;
            }
        }
        return cnt;
    }
};

// [1,1,1,2,3,3,5]
// [2,3,3,5]