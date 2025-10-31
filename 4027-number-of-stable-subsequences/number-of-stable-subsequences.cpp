class Solution {
    typedef long long ll;
    const ll MOD = 1e9 + 7;
public:
    int countStableSubsequences(vector<int>& nums) {
        ll suffix_odd1 = 0, suffix_odd2 = 0;
        ll suffix_even1 = 0, suffix_even2 = 0;

        for (int n: nums) {
            if ((n & 1) == 0) {
                ll new_suffix_even1 = (suffix_even1 + suffix_odd1 + suffix_odd2 + 1) % MOD;
                ll new_suffix_even2 = (suffix_even1 + suffix_even2) % MOD;
                suffix_even1 = new_suffix_even1;
                suffix_even2 = new_suffix_even2; 
            } else {
                ll new_suffix_odd1 = (suffix_odd1 + suffix_even1 + suffix_even2 + 1) % MOD;
                ll new_suffix_odd2 = (suffix_odd1 + suffix_odd2) % MOD;
                suffix_odd1 = new_suffix_odd1;
                suffix_odd2 = new_suffix_odd2; 
            }

        }
        return (suffix_even1 + suffix_even2 + suffix_odd1 + suffix_odd2) % MOD;
    }
};