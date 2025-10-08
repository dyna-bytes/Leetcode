/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// #define DBG
#ifdef DBG
#define debug(x) cout << "[" << __func__ << "] " << #x << " is " << x << endl;
#define debugVect(vect, type, frmt) do { \
    cout << "[" << __func__ << "] " << #vect << " is |"; \
    for (type e: vect) cout << frmt << "|" ; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugVect(vect, type, frmt)
#endif

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        if (root == nullptr) return s;
        
        queue<TreeNode*> q;
        q.push(root);

        while (q.size()) {
            int qsize = q.size();
            for (int i = 0; i < qsize; i++) {
                auto curr = q.front(); q.pop();

                s.append(curr == nullptr ? "-" : to_string(curr->val));
                s.append(" ");

                if (curr == nullptr) continue;
                q.push(curr->left);
                q.push(curr->right);
            }
            s.append(". ");
        }
        debug(s);

        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == string()) return nullptr;

        vector<vector<TreeNode*>> v(1, vector<TreeNode*>(0));
        int level = 0;
        for (int i = 0, j = 0; i < data.size(); i++) {
            for (j = i + 1; j < data.size() && data[j] != ' '; j++) ;

            string ss = data.substr(i, j - i);
            debug(ss);

            if (ss == ".") {
                v.push_back(vector<TreeNode*>(0));
                level++;
            } else
                v[level].push_back(ss == "-" ? nullptr : new TreeNode(stoi(ss)));
            i = j;
        }

        TreeNode* root = v[0][0];
        for (int i = 1, j = 0, k = 0; i < v.size(); i++) {
            for (j = 0, k = 0; j < v[i].size() && k < v[i-1].size(); k++) {
                auto parent = v[i-1][k];
                if (!parent) 
                    continue;
                
                debug(i);
                debug(j);
                debug(k);
                debug(parent->val);

                auto left = v[i][j];
                parent->left = left;
                if (left) debug(left->val);

                if (++j >= v[i].size()) break;
                auto right = v[i][j];
                parent->right = right;
                if (right) debug(right->val);

                if (++j >= v[i].size()) break;
            }
            debugVect(v[i], TreeNode*, (!e ? -1 : e->val));
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));