class Solution {
    string target;
    int n;
    multiset<char> st;
    /*
    Target = [ ... T_i, T_i+1, ... ]
    S = { ... S_i, S_i+1, ... }
    S' = [ ... S'_i, S'_i+1, ... ]


    (1) T_i-1 < S_i-1
        S'_i = min( {S} - {S'} )
    (2) T_i ∈ ({S} - {S'})
        S'_i = T_i
    (3) T_i < Sup( trunc({S} - {S'}, S_i) )
        S'_i = S_i
    */
    bool find(int i, bool is_greater, string& ret) {
        if (i >= n) return is_greater;

        if (is_greater) {
            ret.push_back(*st.begin());
            st.erase(st.begin());
            return find(i+1, true, ret);
        }

        if (st.count(target[i])) {
            ret.push_back(target[i]);
            st.erase(st.find(target[i]));

            if (find(i+1, false, ret)) return true;

            st.insert(target[i]);
            ret.pop_back();
        }

        auto it = st.upper_bound(target[i]);
        if (it == st.end()) return false;
        ret.push_back(*it);
        st.erase(it);
        return find(i+1, true, ret);
    }
public:
    string lexGreaterPermutation(string s, string target) {
        this->target = target;
        n = target.size();
        st = multiset<char>(s.begin(), s.end());

        string ret;
        if (!find(0, false, ret)) return "";
        return ret;
    }
};