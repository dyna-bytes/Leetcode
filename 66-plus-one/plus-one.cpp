class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        vector<int> ret(n, 0);

        int c = 1;
        for (int i = n - 1; i >= 0; i--) {
            int x = digits[i] + c;
            c = x / 10;
            ret[i] = x % 10;
        }

        if (c) {
            vector<int> ret2(n + 1, 0);
            ret2[0] = c;
            for (int i = 0; i < n; i++)
                ret2[i + 1] = ret[i];
            return ret2;
        }
        return ret;
    }
};