class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        
        int ret = 1;
        unordered_set<int> set;
        for(int num : nums)
            set.insert(num);
        
        for(int num : set){
            if(set.find(num - 1) == set.end()){
                int streakEnd;
                for(streakEnd = num; set.find(streakEnd) != set.end(); streakEnd++);
                
                ret = max(ret, streakEnd - num);
            }
        }
        
        return ret;
    }
};