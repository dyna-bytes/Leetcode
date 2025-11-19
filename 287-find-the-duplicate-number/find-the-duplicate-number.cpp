#define debug(x) cout << #x << " is " << x << endl;
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size() - 1;
        
        int t = 0, h = 0;
        do {
            t = nums[t];
            h = nums[nums[h]];
        } while (t != h);
        // debug(t);

        t = 0;
        do {
            t = nums[t];
            h = nums[h];
        } while (t != h);
        // debug(t);

        return h;
    }
};