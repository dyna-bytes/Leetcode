class Solution {
    int reverse(int n) {
        int x = 0;
        while (n > 0) {
            x *= 10;
            x += (n % 10);
            n /= 10;
        }
        return x;
    }
public:
    int minMirrorPairDistance(vector<int>& nums) {
        int n = nums.size();
        int minlen = INT_MAX;
        unordered_map<int, int> um;

        for (int i = 0; i < n; i++) {
            int x = nums[i];
            int r = reverse(x);
            if (um.count(x))
                minlen = min(minlen, i - um[x]);

            um[r] = i;
        }

        if (minlen == INT_MAX) return -1;
        return minlen;
    }
};