#define debug(x) cout << #x << " is " << x << endl;
struct Trie {
    string serial;
    unordered_map<string, Trie*> children;
};

class Solution {
    unordered_map<string, int> freq;
    vector<vector<string>> ans;

    void serialize(Trie* curr) {
        if (curr->children.empty()) return;

        vector<string> v;
        for (auto& [folder, node]: curr->children) {
            serialize(node);
            v.push_back(folder + "(" + node->serial + ")");
        }

        sort(v.begin(), v.end());
        
        for (auto& s: v)
            curr->serial.append(s);

        freq[curr->serial]++;
    }


    void dfs(Trie* curr, vector<string>& path) {
        if (freq[curr->serial] > 1) return;

        if (!path.empty()) ans.push_back(path);

        for (auto& [folder, node]: curr->children) {
            path.push_back(folder);
            dfs(node, path);
            path.pop_back();   
        }
    }
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        Trie* root = new Trie();
        for (auto& path: paths) {
            auto curr = root;
            for (string& folder: path) {
                if (curr->children.count(folder) == 0) 
                    curr->children[folder] = new Trie();
                curr = curr->children[folder];
            }
        }

        serialize(root);
        vector<string> dfs_path;
        dfs(root, dfs_path);
        return ans;
    }
};