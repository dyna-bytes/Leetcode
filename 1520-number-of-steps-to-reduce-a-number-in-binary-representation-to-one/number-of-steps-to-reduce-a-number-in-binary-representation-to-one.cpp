class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
public:
    int numSteps(string s) {
        int step = 0;
        while (s != "1") {
            if (s.back() == '0') s.pop_back();
            else if (s.back() == '1') {
                string r;
                char c = '1';
                for (int i = s.size() - 1; i >= 0; i--) {
                    int x = (s[i] - '0') + (c - '0');
                    if (x == 2) {
                        r.push_back('0');
                        c = '1';
                    } else if (x == 1) {
                        r.push_back('1');
                        c = '0';
                    } else if (x == 0) {
                        r.push_back('0');
                        c = '0';
                    }
                }

                if (c == '1') r.push_back('1');

                reverse(r.begin(), r.end());
                s = r;
            }

            step++;
        }
        return step;
    }
};