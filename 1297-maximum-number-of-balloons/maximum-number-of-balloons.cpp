class Solution {
public:
    int maxNumberOfBalloons(string text) {
        string balloon = "balloon";
        unordered_map<char, int> um;
        for (char c: text) {
            um[c]++;
        }

        int min_chars = text.size();
        int min_ls = text.size();
        int min_os = text.size();
        for (char c: balloon) {
            if (c == 'l') min_ls = um[c];
            else if (c == 'o') min_os = um[c];
            else min_chars = min(min_chars, um[c]);
        }

        return min({min_chars, min_ls/2, min_os/2});
    }
};