class Solution {
    string s;
    vector<vector<int>> dp;
    bool isPalindrome(int l, int r) {
        if (r < 0 || l >= s.size()) return false;

        int& ret = dp[l][r];
        if (ret != -1) return ret;
        
        if (l == r) return ret = true;
        if (l + 1 == r) return ret = (s[l] == s[r]);

        if (isPalindrome(l+1, r-1) && s[l] == s[r]) 
            return ret = true;

        return ret = false;
    }
public:
    string longestPalindrome(string s) {
        this->s = s;
        dp.resize(s.size() + 1, vector<int>(s.size() + 1, -1));

        int maxsize = 0;
        string ans;
        for (int i = 0; i < s.size(); i++) {
            for (int j = i; j < s.size(); j++) {
                if (isPalindrome(i, j) && maxsize < (j - i + 1)) {
                    maxsize = (j - i + 1);
                    ans = s.substr(i, j - i + 1);
                } 
            }
        }
        return ans;
    }
};