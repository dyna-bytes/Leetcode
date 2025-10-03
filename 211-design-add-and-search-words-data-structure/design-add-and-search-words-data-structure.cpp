class WordDictionary {
    WordDictionary* next[26];
    bool isLeaf;

    void __addWord(const char* c) {
        if (*c == '\0') {
            isLeaf = true;
            return;
        }

        int n = *c - 'a';
        if (!next[n]) next[n] = new WordDictionary();
        next[n]->__addWord(c + 1);
    }

    bool __search(const char* c) {
        if (*c == '\0') return isLeaf;
        if (*c == '.') {
            for (int i = 0; i < 26; i++)
                if (next[i] && next[i]->__search(c + 1))
                        return true;
            return false;
        }
        
        int n = *c - 'a';
        if (!next[n]) return false;
        return next[n]->__search(c + 1);
    }
public:
    WordDictionary() {
        fill(next, next + 26, nullptr);
        isLeaf = false;
    }
    
    void addWord(string word) {
        const char*c = word.c_str();
        __addWord(c);
    }
    
    bool search(string word) {
        const char*c = word.c_str();
        return __search(c);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */