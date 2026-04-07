class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
    #define debugVect(v) do {\
        cout << #v << " is |"; \
        for (auto e: v) cout << e << "|"; \
        cout << endl; \
    } while (0)
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        vector<int> st;
        int n = pushed.size();
        int i, j;
        for (i = 0, j = 0; i < n && j < n; ) {
            while (st.size() && st.back() == popped[j]) {
                st.pop_back();
                j++;
            }
            st.push_back(pushed[i++]);
        }

        while (st.size() && j < n && st.back() == popped[j]) {
            st.pop_back();
            j++;
        }

        if (st.empty()) return true;
        return false;
    }
};