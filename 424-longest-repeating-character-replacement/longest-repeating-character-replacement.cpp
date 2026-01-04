class Solution {
    int getMaxlen(const string& str, int k, char T) {
        int s = 0;
        int e = 0;
        int n = str.size();
        int maxlen = 0;
        for (e = 0; e < n; e++) {
            if (str[e] == T) ;
            else if (k > 0) k--;
            else { 
                while (s < e && str[s] == T)
                    s++;
                s++;
            }
            maxlen = max(maxlen, e - s + 1);
        }
        return maxlen;
    }
public:
    int characterReplacement(string str, int k) {
        set<char> chars(str.begin(), str.end());
        int ret = 0;
        for (char ch: chars) 
            ret = max(ret, getMaxlen(str, k, ch));
        return ret;
    }
};