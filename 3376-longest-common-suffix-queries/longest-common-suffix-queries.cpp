#define debug(x) cout << #x << " is " << x << endl;

struct Trie {
    bool isLeaf;
    Trie* next[26];
    int best_idx;
    int min_len;

    Trie() {
        isLeaf = false;
        best_idx = -1, min_len = INT_MAX;
        fill(next, next + 26, nullptr);
    }
    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (next[i]) delete next[i];
    }

    void insert(const char *c, const int idx, const int len) {
        int x = *c - 'a';

        if (min_len > len) {
            min_len = len;
            best_idx = idx;
        }

        if (*c == '\0') {
            isLeaf = true;
            return;
        }

        if (!next[x]) next[x] = new Trie();
        next[x]->insert(c + 1, idx, len);   
    }

    int search(const char *c) {
        int x = *c - 'a';
        if (*c == '\0' || !next[x]) {
            return best_idx;
        }
        return next[x]->search(c + 1);
    }
};

class Solution {
    Trie root;
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        for (int i = 0; i < wordsContainer.size(); i++) {
            string& word = wordsContainer[i];
            reverse(word.begin(), word.end());
            root.insert(word.c_str(), i, word.size());
        }
        
        vector<int> ret(wordsQuery.size());
        for (int i = 0; i < wordsQuery.size(); i++) {
            string& word = wordsQuery[i];
            reverse(word.begin(), word.end());
            ret[i] = root.search(word.c_str());
        }
        return ret;
    }
};