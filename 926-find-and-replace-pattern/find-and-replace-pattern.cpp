class Solution {
    bool isPermutation(string& word, string& pattern) {
        int N = word.size();
        unordered_map<char, int> hash_word;
        unordered_map<char, int> hash_pattern;
        vector<int> remap_word(N);
        vector<int> remap_pattern(N);

        int unique_cnt = 0;
        for (int i = 0; i < N; i++) {
            char w = word[i];
            if (!hash_word[w]) hash_word[w] = ++unique_cnt;

            remap_word[i] = hash_word[w];
        }

        unique_cnt = 0;
        for (int i = 0; i < N; i++) {
            char w = pattern[i];
            if (!hash_pattern[w]) hash_pattern[w] = ++unique_cnt;

            remap_pattern[i] = hash_pattern[w];
        }

        return remap_word == remap_pattern;
    }
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> ans;
        for (string& word: words) {
            if (word.size() != pattern.size()) continue;

            if (isPermutation(word, pattern))
                ans.push_back(word);
        }

        return ans;
    }
};