class Solution {
    int ctoi(char c) { return c - '0'; }
public:
    bool checkOnesSegment(string s) {
        int n = s.size();
        
        int ones = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') continue;
            
            int j = i;
            for (; j < n && s[j] == '1'; ++j)
                ;
            ones++;

            i = j;
        }
        return ones == 1;
    }
};