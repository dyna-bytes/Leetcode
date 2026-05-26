class Solution {
public:
    int numberOfSpecialChars(string word) {
        unordered_map<char, int> hash;
        vector<int> ret(26, 0);
        for (char& c: word) {
            if ('a' <= c && c <= 'z') {
                if (hash[c - 'a' + 'A']) ret[c - 'a'] = true;
            } else {
                if (hash[c - 'A' + 'a']) ret[c - 'A'] = true;
            }
            hash[c] = true;
        }
        return count(ret.begin(), ret.end(), true);
    }
};