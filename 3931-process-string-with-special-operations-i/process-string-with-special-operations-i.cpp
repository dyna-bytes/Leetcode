class Solution {
public:
    string processStr(string s) {
        string ret;
        for (char c: s) {
            if (c >= 'a' && c <= 'z') ret.push_back(c);
            else if (c == '*' && ret.size()) ret.pop_back();
            else if (c == '#') {
                int n = ret.size();
                for (int i = 0; i < n; i++)
                    ret.push_back(ret[i]);
            } else if (c == '%')
                reverse(ret.begin(), ret.end());
        }
        return ret;
    }
};