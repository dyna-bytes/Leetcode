class Solution {
public:    
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1); // dp[n] : n번째 char까지 wordBreak를 만족하는가
        
        for(int i = 0; i < n; i++){
            string curr_s = s.substr(i); // [i, end)까지의 문자열
            
            for(string word: wordDict){
                if(isMatch(curr_s, word)){
                    int len = word.size();
                    
                    if(i == 0) dp[i] = true;
                    if(dp[i+len] == false && dp[i] == true) dp[i+len] = true;
                }
            }
        }
        
        return dp[n];
    }
    
    bool isMatch(string s, string word){
        if(s.size() < word.size()) return false;
        return s.substr(0, word.size()) == word;
    }
};