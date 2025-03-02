class Solution {
public:
    unordered_map<string, int> matched;
    bool isSubsequence(string& s, string& word) {
        if (matched[word]) return true;
        
        for (int i = 0, j = 0; i < s.size(); i++) {
            if (s[i] == word[j]) j++;
            
            if (j == word.size()) {
                matched[word] = true;
                return true;
            }
        }
        return false;
    } 

    int numMatchingSubseq(string s, vector<string>& words) {
        int match = 0;
        for (string& word: words) {
            if (isSubsequence(s, word))
                match++;
        }
        return match;
    }
};