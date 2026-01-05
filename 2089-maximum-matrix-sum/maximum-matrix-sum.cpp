class Solution {
    typedef long long ll;
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        vector<ll> nums;
        int negs = 0;
        ll min_v = INT_MAX;
        for (auto& row: matrix)
            for (int v: row) {
                if (v <= 0) negs++;
                nums.push_back(abs(v));
                min_v = min(min_v, (ll)abs(v));
            }

        ll sum = accumulate(nums.begin(), nums.end(), 0LL);
        if (negs % 2 == 0)
            return sum;

        return sum - 2*min_v;
    }
};