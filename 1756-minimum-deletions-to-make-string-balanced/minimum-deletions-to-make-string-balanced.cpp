class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();
        vector<int> pref_b(n, 0); // pref_b[i]: number of b's before i
        vector<int> suff_a(n, 0); // suff_a[i]: number of a's after i

        for (int i = 0; i < n - 1; i++) 
            pref_b[i + 1] = pref_b[i] + (s[i] == 'b');
        

        for (int i = n - 1; i > 0; i--)
            suff_a[i - 1] = suff_a[i] + (s[i] == 'a');

        int min_del = n;
        for (int i = 0; i < n; i++)
            min_del = min(min_del, pref_b[i] + suff_a[i]);
        return min_del;
    }
};