#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    typedef pair<int, int> pii;
public:
    string removeDuplicates(string s, int k) {
        vector<pii> st;
        for (char c: s) {
            int x = c - 'a';
            int cnt = (st.size() && st.back().first == x) ? 
                st.back().second + 1 : 1;
            
            st.push_back({x, cnt});
            if (cnt >= k) {
                assert(st.size() >= k);
                for (int i = 0; i < k; i++)
                    st.pop_back();
            }
        }

        string ans;
        for (int i = 0; i < st.size(); i++)
            ans += (st[i].first + 'a');
        return ans;
    }
};