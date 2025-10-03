class Trie {
    Trie* next[26];
    bool isLeaf;
    void __insert(const char* c) {
        if (*c == '\0') {
            isLeaf = true;
            return;
        }

        int n = *c - 'a';
        if (!next[n]) next[n] = new Trie();

        next[n]->__insert(c + 1);
    }

    bool __search(const char* c) {
        if (*c == '\0') return isLeaf;

        int n = *c - 'a';
        if (!next[n]) return false;

        return next[n]->__search(c + 1);
    }

    bool __startsWith(const char* c) {
        if (*c == '\0') return true;

        int n = *c - 'a';
        if (!next[n]) return false;

        return next[n]->__startsWith(c + 1);
    }
public:
    Trie() {
        fill(next, next + 26, nullptr);
        isLeaf = false;
    }
    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (next[i]) delete(next[i]);
    }
    
    void insert(string word) {
        const char* c = word.c_str();
        __insert(c);
    }
    
    bool search(string word) {
        const char* c = word.c_str();
        return __search(c);
    }
    
    bool startsWith(string prefix) {
        const char* c = prefix.c_str();
        return __startsWith(c);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */