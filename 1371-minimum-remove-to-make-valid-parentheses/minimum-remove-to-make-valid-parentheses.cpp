class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
public:
    string minRemoveToMakeValid(string s) {
        vector<int> st;
        int left = 0;
        for (char c: s) {
            if (c == ')') {
                if (left == 0) continue;

                left--;
                st.push_back(c);
            } else if (c == '(') {
                left++;
                st.push_back(c);
            } else
                st.push_back(c);
        }

        string ret;
        for (int i = st.size() - 1; i >= 0; i--) {
            char c = st[i];
            if (c == '(') {
                if (left > 0) {
                    left--;
                    continue;
                }
                ret.push_back(c);
            } else
                ret.push_back(c);
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }
};