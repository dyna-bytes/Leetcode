class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        map<int, int> hash;
        for (int num: nums)
            hash[num]++;

        
        int i = 0, j = 0;
        for (auto [num, cnt]: hash) {
            for (j = 0; j < min(cnt, 2); j++) {
                nums[i] = num;
                i++;
            }
        }
        return i;
    }
};