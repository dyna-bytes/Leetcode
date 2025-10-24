class Solution {
public:
    bool isValid(string s) {
        int opcnt = 0;
        stack<char> st;
        for (char c : s) {
            if (c == ')') {
                if (!st.empty() &&st.top() == '(')
                    st.pop(), opcnt++;
            } else if (c == '}') {
                if (!st.empty() &&st.top() == '{')
                    st.pop(), opcnt++;
            } else if (c == ']') {
                if (!st.empty() &&st.top() == '[')
                    st.pop(), opcnt++;
            } else {
                st.push(c), opcnt++;
            }
        }

        return s.size() == opcnt && st.size() == 0;
    }
};