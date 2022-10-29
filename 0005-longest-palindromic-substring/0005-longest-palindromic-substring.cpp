typedef vector<int> vint;
class Solution {
public:
    vector<vint> dp;
    bool isPalindrome(int S, int E, string& str) {
        int& ret = dp[S][E];
        if (ret != -1) return ret;
        if (S == E) return ret = true;
        if (S + 1 == E) return ret = (str[S] == str[E]);

        return ret = (str[S] == str[E]) && isPalindrome(S+1, E-1, str);
    }
    string longestPalindrome(string str) {
        int N = str.size();
        dp.resize(N, vint(N, -1));    
        
        string ret;
        int max_len = 0;
        for (int S = 0; S < N; S++)
            for (int E = S; E < N; E++)
                if (isPalindrome(S, E, str)) {
                    int len = E - S + 1;
                    if (max_len < len) {
                        ret = str.substr(S, len);
                        max_len = len;
                    }
                }
        return ret;
    }
};