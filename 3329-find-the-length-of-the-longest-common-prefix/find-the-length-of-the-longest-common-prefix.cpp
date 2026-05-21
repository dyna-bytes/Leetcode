class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<string> um;
        for (int a: arr1) {
            string s = to_string(a);
            for (int i = 1; i <= s.size(); i++) {
                string p = s.substr(0, i);
                um.insert(p);
            }
        }

        int ret = 0;
        for (int a: arr2) {
            string s = to_string(a);
            for (int i = 1; i <= s.size(); i++) {
                string p = s.substr(0, i);
                if (um.count(p))
                    ret = max(ret, i);
            }
        }
        return ret;
    }
};