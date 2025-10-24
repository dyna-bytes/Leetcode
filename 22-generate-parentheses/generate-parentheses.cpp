class Solution {
    const char L = '(';
    const char R = ')';
    vector<string> ret;
    void f(int i, int Ls, int n, string& s) {
        if (i == 2*n) {
            if (Ls == 0)
                ret.push_back(s);
            return;
        }

        if (Ls > 0) {
            s.push_back(R);
            f(i+1, Ls-1, n, s);
            s.pop_back();
        }

        if (Ls < n) {
            s.push_back(L);
            f(i+1, Ls+1, n, s);
            s.pop_back();
        } 
    }
public:
    vector<string> generateParenthesis(int n) {
        string s;
        f(0, 0, n, s);
        return ret;
    }
};