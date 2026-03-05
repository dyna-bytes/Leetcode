class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        int start_zero = 0;
        for (int i = 0; i < n; ++i) {
            if ((i % 2 == 0 && s[i] == '1') ||
            (i % 2 == 1 && s[i] == '0'))
                start_zero++;
        }

        int start_one = 0;
        for (int i = 0; i < n; ++i) {
            if ((i % 2 == 0 && s[i] == '0') ||
            (i % 2 == 1 && s[i] == '1'))
                start_one++; 
        }

        return min(start_zero, start_one);
    }
};