class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int n = s.size();
        vector<vector<int>> occ(26, vector<int>(2, -1));

        for (int i = 0; i < n; i++) 
            for (int j = 0; j < 26; j++) {
                if (s[i] == 'a' + j) {
                    if (occ[j][0] == -1) occ[j][0] = i; // first occurancy
                    else occ[j][1] = i; // last occurancy
                }
            }
        
        unordered_set<string> seen;
        for (int i = 1; i <= n-1; i++) {
            for (int j = 0; j < 26; j++) {
                char c = 'a' + j;
                string palindrome = string(1, c) + s[i] + string(1, c);
                if (occ[j][0] < i && i < occ[j][1] && seen.count(palindrome) == 0) {
                    seen.insert(palindrome);
                }
            }
        }
        
        return seen.size();
    }
};

/*      0123456  
 * s = "bbcbaba"
 * a = (4, 6)
 * b = (0, 5)
 * c = (2, 2)

 * for (1 <= i <= 5)
 * i = 1 (b) -> 1 is in (0, 5)
 * i = 2 (c) -> 2 is in (0, 5)
 * i = 3 (b) -> 3 is in (0, 5) -> already counted on i = 1
 * i = 4 (a) -> 4 is in (0, 5)
 * i = 5 (b) -> 5 is on (4, 6)
 */