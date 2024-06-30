class Solution {
public:
    vector<string> words;
    vector<int> groups;
    vector<int> record;    
    vector<int> mem;
    
    int f(int k) {
        if (k <= -1) {
            return 0;
        }
        
        int& ret = mem[k];
        if (ret != -1) return ret;
        
        if (k == 0) {
            record.push_back(0);
            return ret = 1;
        }
        
        int n, m;
        for (n = k - 1; n >= 0; n--){
            if (groups[n] != groups[k])
                break;
        }
        for (m = k - 1; m >= 0; m--)
            if (groups[m] == groups[k])
                break;
        
        int differ_bit = f(n) + 1;
        int same_bit = f(m);
        
        if (differ_bit > same_bit)
            record.push_back(k);
        return ret = max(differ_bit, same_bit);
    }
    
    vector<string> getLongestSubsequence(vector<string>& words, vector<int>& groups) {
        this->words = words;
        this->groups = groups;
        int len = groups.size();
        mem.resize(len + 1, -1);
        
        f(len-1);
        
        vector<string> ret;
        for (int index: record) {
            ret.push_back(words[index]);
        }
        
        return ret;
    }
};