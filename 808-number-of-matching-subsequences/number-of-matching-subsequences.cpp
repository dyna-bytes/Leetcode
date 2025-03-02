class Solution {
public:
    vector<set<int>> dict;

    bool isSubsequence(string& s, string& word) {
        int prev_index = -1;

        for (char c: word) {
            auto it = dict[c].upper_bound(prev_index);
            if (it == dict[c].end()) return false;
            if (*it < prev_index) return false;
            prev_index = *it;
        }
        return true;
    } 

    int numMatchingSubseq(string s, vector<string>& words) {
        dict.resize('z' + 1);
        for (int i = 0; i < s.size(); i++)
            dict[s[i]].insert(i);

        int match = 0;
        for (string& word: words) {
            if (isSubsequence(s, word))
                match++;
        }
        return match;
    }
};