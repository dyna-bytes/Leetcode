class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();
        int k = n / 8;
        int ret = 0;

        int i;
        for (i = 1; i <= k; ++i)
            ret += (8 * i);
        ret += i * (n % 8);
        return ret;
    }
};