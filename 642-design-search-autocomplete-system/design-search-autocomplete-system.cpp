#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << "[" << __func__ << "](" << __LINE__ << ") " << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)

class Trie {
    bool isLeaf = false;
    map<char, Trie*> next;
public:
    Trie() {
    }

    void insert(char *c) {
        if (*c == '\0') {
            isLeaf = true;
            return;
        }

        if (next.count(*c) == 0) next[*c] = new Trie();
        return next[*c]->insert(c + 1);
    }

    void search(char *c, string& path, vector<string>& ret) {
        if (*c == '\0') {
            if (isLeaf) {
                ret.push_back(path);
            }

            for (auto& [nc, nxt]: next) {
                path.push_back(nc);
                nxt->search(c, path, ret);
                path.pop_back();
            }
            return;
        }

        if (next.count(*c) == 0) return;
        path.push_back(*c);
        return next[*c]->search(c + 1, path, ret);
    }

    void insert(string& s) {
        insert((char *)s.c_str());
    }

    vector<string> search(string& s) {
        vector<string> ret;
        string root = "";
        search((char *)s.c_str(), root, ret);
        return ret;
    }
};

class AutocompleteSystem {
    Trie trie;
    string str;
    unordered_map<string, int> hot;
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        for (int i = 0; i < sentences.size(); i++) {
            trie.insert(sentences[i]);
            hot[sentences[i]] = times[i];
        }
    }
    
    vector<string> input(char c) {
        if (c == '#') {
            trie.insert(str);
            hot[str]++;

            str = "";
            return vector<string>();
        }

        str.push_back(c);
        vector<string> ret = trie.search(str);
        sort(ret.begin(), ret.end(), [&](const string& a, const string& b){
            if (hot[a] == hot[b]) return a < b;
            return hot[a] > hot[b];
        });

        if (ret.size() < 3) return ret;
        return { ret[0], ret[1], ret[2] };
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */