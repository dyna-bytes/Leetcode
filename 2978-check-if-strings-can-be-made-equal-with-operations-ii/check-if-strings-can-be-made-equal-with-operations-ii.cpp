class Solution {
public:
    bool checkStrings(string s1, string s2) {
        int n = s1.size();
        multiset<int> ms1_odd, ms1_even;
        multiset<int> ms2_odd, ms2_even;
        
        for (int i = 0; i < n; i++) {
            if (i % 2) ms1_odd.insert(s1[i]);
            else ms1_even.insert(s1[i]);
        }

        for (int i = 0; i < n; i++) {
            if (i % 2) ms2_odd.insert(s2[i]);
            else ms2_even.insert(s2[i]);
        }

        return (ms1_odd == ms2_odd) && (ms1_even == ms2_even);
    }
};