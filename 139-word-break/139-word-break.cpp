class Solution {
public:
    vector<int> dp;
    
    bool wordBreak(string s, vector<string>& wordDict) {
        dp.resize(s.size() + 1, -1);
        return wrdbrk(s, wordDict);
    }
    
    bool isMatch(string s, string word){
        if(s.size() < word.size()) return false;
        return s.substr(0, word.size()) == word;
    }
    
    bool wrdbrk(string s, vector<string>& wordDict){
        // we have 2 choices
        // if word in wordDict matches the string S,
        //      extract the word from the string S 
        //      or don't extract the word and try to find another word that matches with S
        int& ret = dp[s.size()];
        if(ret != -1) return ret;
        if(s.size() == 0) return ret = true;
        
        ret = false;
        for(string word : wordDict){
            if(isMatch(s, word)){
                string next_s = s.substr(word.size());
                ret |= wrdbrk(next_s, wordDict);
            }   
        }
        return ret;   
    }
};