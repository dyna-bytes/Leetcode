class Trie {
    Trie* children[26];
    bool is_leaf;
public:
    Trie() {
        memset(children, 0, sizeof(children));
    }
    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (children[i])
                delete children[i];
    }
    void insert(const char *str) {
        if (*str == '\0') {
            this->is_leaf = true;
            return;
        }
        int x = *str - 'a';
        if (!children[x]) children[x] = new Trie();
        return children[x]->insert(str + 1);
    }
    bool search(const char *str) {
        if (*str == '\0') return this->is_leaf;

        int ret = false;
        if (*str == '.') {
            for (int i = 0; i < 26; i++) {
                if (!children[i]) continue;
                ret += children[i]->search(str + 1);
            }
            return ret;
        }
        
        int x = *str - 'a';
        if (!children[x]) return false;
        return children[x]->search(str + 1);
    }
};

class Solution {
    Trie root;
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        for (string& word: dictionary) {
            root.insert(word.c_str());
        }

        vector<string> ret;
        auto find = [&](string& query) {
            int sz = query.size();
            if (sz == 1) return true;
            
            for (int i = 0; i + 1 < sz; i++) {
                for (int j = i + 1; j < sz; j++) {
                    string word = query;
                    word[i] = word[j] = '.';
                    if (root.search(word.c_str())) 
                        return true;
                }
            }
            return false;
        };

        for (string& query: queries) {
            if (find(query)) ret.push_back(query);
        }
        return ret;
    }
};