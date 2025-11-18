#define debug(x) cout << #x << " is " << x  << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while(0)
class Solution {
    string f(string& s) {
        if (s.size() == 0) return s;
        vector<string> v;
        int open = 0;
        int prev_i = 0;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '1') open++;
            else open--;

            if (open == 0)  {
                v.push_back(s.substr(prev_i, i - prev_i + 1));
                prev_i = i + 1;
            }
        }

        if (v.size() == 1) {
            string ss = s.substr(1, s.size() - 2);
            return "1" + f(ss) + "0";
        }

        for (string& str: v)
            str = f(str);

        sort(v.begin(), v.end(), [](string& a, string& b){
            return a > b;
        });

        string ret;
        for (string& str: v) ret.append(str);
        return ret;
    }
public:
    string makeLargestSpecial(string s) {
        return f(s);
    }
};