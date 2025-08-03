class Solution {
public:
    int numSplits(string s) {
        int n = s.size();
        vector<int> pref(n, 0); // pref[i] = distinct chars in [0, i] 
        vector<int> suff(n, 0); // suff[i] = distinct chars in [i, n]
        unordered_map<int, int> p_hash;
        unordered_map<int, int> s_hash;

        pref[0] = 1;
        p_hash[s[0]] = true;
        for (int i = 0; i < n - 1; i++) {
            pref[i+1] = pref[i] + !(p_hash[s[i+1]]);

            if (!p_hash[s[i+1]]) p_hash[s[i+1]] = true;
        }

        suff[n-1] = 1;
        s_hash[s[n-1]] = true;
        for (int i = n - 1; i > 0; i--) {
            suff[i-1] = suff[i] + !(s_hash[s[i-1]]);

            if (!s_hash[s[i-1]]) s_hash[s[i-1]] = true;
        }

        int good = 0;
        for (int i = 0; i < n - 1; i++)
            if (pref[i] == suff[i+1]) good++;

        return good;
    }
};