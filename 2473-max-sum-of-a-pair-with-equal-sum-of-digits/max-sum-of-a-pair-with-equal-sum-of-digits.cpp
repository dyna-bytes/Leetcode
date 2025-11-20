class Solution {
    int get_digit_sum(int num) {
        int sum = 0;
        
        while (num > 0) {
            int digit = num % 10;
            sum += digit;
            num /= 10;
        }
        return sum;
    }
public:
    int maximumSum(vector<int>& nums) {
        map<int, multiset<int>> um;
        for (int num: nums) {
            int dsum = get_digit_sum(num);

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