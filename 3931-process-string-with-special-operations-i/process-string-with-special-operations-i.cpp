class Solution {
public:
    string processStr(string s) {
        string ret;
        for (char c: s) {
            if (c >= 'a' && c <= 'z') ret.push_back(c);
            else if (c == '*' && ret.size()) ret.pop_back();
            else if (c == '#') ret = ret + ret;
            else if (c == '%') reverse(ret.begin(), ret.end());
        }
        return ret;
    }
};