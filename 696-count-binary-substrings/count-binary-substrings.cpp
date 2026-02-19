class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
public:
    int countBinarySubstrings(string s) {
        int n = s.size();
        int ret = 0;
        int mask = 0;
        int i = 0, j = -1;
        for (; i < n && j < n; i++) {
            while (i + 1 < n && s[i] == s[i + 1]) i++;
            int new_mask = i - j;
            ret += min(mask, new_mask);
            mask = new_mask;

            j = i;
        }
        return ret;
    }
};