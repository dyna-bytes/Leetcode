class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> us, visited;
        for (int n: nums) us.insert(n);
        
        int ret = 0;
        for (int n: us) {
            if (us.count(n - 1) || visited.count(n)) continue;

            int i;
            for (i = 0; us.count(n + i); i++) 
                visited.insert(n + i);
            ret = max(ret, i);
        }
        return ret;
    }
};