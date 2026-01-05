class Solution {
    typedef long long ll;
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        vector<ll> nums;
        int negs = 0;
        for (auto& row: matrix)
            for (int v: row) {
                if (v <= 0) negs++;
                nums.push_back(abs(v));
            }

        ll sum = accumulate(nums.begin(), nums.end(), 0LL);
        if (negs % 2 == 0)
            return sum;

        sort(nums.begin(), nums.end());
        ll min_v = nums[0];
        return sum - 2*min_v;
    }
};