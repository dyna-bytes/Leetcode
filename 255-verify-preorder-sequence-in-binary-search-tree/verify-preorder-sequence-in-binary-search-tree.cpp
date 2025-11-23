class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        stack<int> st;
        int lower_bound = INT_MIN;

        for (int node: preorder) {
            while (st.size() && st.top() < node) {
                lower_bound = max(lower_bound, st.top());
                st.pop();
            }

            if (lower_bound >= node) return false;
            st.push(node);
        }
        return true;
    }
};