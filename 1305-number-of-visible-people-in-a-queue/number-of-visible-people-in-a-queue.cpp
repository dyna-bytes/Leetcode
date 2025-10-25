class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        int n = heights.size();
        stack<int> st; // monoton decreasing stack
        vector<int> ret(n, 0);
        
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && st.top() < heights[i]) {
                st.pop();
                ret[i]++;
            }
            if (st.size()) ret[i]++;
            st.push(heights[i]);
        }
        return ret;
    }
};