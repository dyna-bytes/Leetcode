class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        int k = indices.size();
        unordered_map<int, string> stridx_to_target;
        unordered_map<int, int> kth_operation;
        for (int i = 0; i < k; i++) {
            int stridx = indices[i];
            if (stridx_to_target.count(stridx)) continue;
            kth_operation[stridx] = i;

            if (s.substr(stridx, sources[i].size()) == sources[i]) {
                stridx_to_target[stridx] = targets[i];
            }
        }

        string ret;
        for (int stridx = 0; stridx < s.size(); ) {
            if (stridx_to_target.count(stridx)){
                int i = kth_operation[stridx];
                ret += stridx_to_target[stridx];
                cout << sources[i] << " ";
                stridx += sources[i].size();
            }
            else {
                ret += s[stridx];
                stridx++;
            }
        }
        return ret;
    }
};