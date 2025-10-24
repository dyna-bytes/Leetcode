class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == ')') {
                if (st.empty()) 
                    return false;
                else if (st.top() == '(')
                    st.pop();
                else
                    return false;
            } else if (c == '}') {
                if (st.empty()) 
                    return false;
                else if (st.top() == '{')
                    st.pop();
                else
                    return false;
            } else if (c == ']') {
                if (st.empty()) 
                    return false;
                else if (st.top() == '[')
                    st.pop();
                else
                    return false;
            } else
                st.push(c);
        }

        return st.size() == 0;
    }
};