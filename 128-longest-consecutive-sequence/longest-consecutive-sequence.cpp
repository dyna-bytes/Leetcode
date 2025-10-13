class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> us;
        for (int n: nums) us.insert(n);
        
        int ret = 0;
        for (int n: us) {
            if (us.count(n - 1)) continue;

            int i;
            for (i = 1; us.count(n + i); i++) ;
            ret = max(ret, i);
        }
        return ret;
    }
};