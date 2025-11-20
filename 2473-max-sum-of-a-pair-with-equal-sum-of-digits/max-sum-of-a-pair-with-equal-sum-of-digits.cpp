class Solution {
public:
    int maximumSum(vector<int>& nums) {
        unordered_map<int, multiset<int>> um;
        for (int num: nums) {
            string s = to_string(num);
            int dsum = 0;
            for (int i = 0; i < s.size(); i++)
                dsum += (s[i] - '0');

            um[dsum].insert(num);
        }

        int maxval = -1;
        for (auto& [dsum, ms]: um) {
            if (ms.size() < 2) continue;

            maxval = max(maxval, *ms.rbegin() + *next(ms.rbegin()));
        }
        return maxval;
    }
};