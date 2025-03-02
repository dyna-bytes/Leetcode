class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        // Preprocess s: for each letter, store its indices in s.
        vector<vector<int>> char_indices(26);
        for (int i = 0; i < s.size(); i++) {
            char_indices[s[i] - 'a'].push_back(i);
        }

        int count = 0;
        for (const string &word : words) {
            int prev_index = -1;
            bool is_subseq = true;
            for (char c : word) {
                const auto &indices = char_indices[c - 'a'];
                // Use binary search to find the index greater than prev_index.
                auto it = upper_bound(indices.begin(), indices.end(), prev_index);
                if (it == indices.end()) { 
                    is_subseq = false;
                    break;
                }
                prev_index = *it;
            }
            if (is_subseq)
                count++;
        }
        return count;
    }

};