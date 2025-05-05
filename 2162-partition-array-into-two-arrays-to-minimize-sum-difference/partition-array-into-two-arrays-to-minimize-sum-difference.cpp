// #define DBG
#ifdef DBG
#define debug(x)                                                               \
    std::cout << "[ " << __func__ << "](" << __LINE__ << ") " << #x << " is "  \
              << x << endl
#else
#define debug(x)
#endif

typedef unsigned long long ull;
class Solution {
    int N;
    double target;
    vector<set<int>> leftsubsetsum,
        rightsubsetsum; // {k elems, {subsetsum}}

    void subsetsum(int curr, vector<int>& nums, int selected,
                   vector<set<int>>& ret) {
        if (curr == nums.size()) {
            int sum = 0, k = 0;
            for (ull bit = 1, i = 0; i < curr; bit <<= 1, i++) {
                if (bit & selected)
                    sum += nums[i], k++;
            }

            ret[k].insert(sum);
            return;
        }

        selected |= (1 << curr);
        subsetsum(curr + 1, nums, selected, ret);
        selected &= ~(1 << curr);

        subsetsum(curr + 1, nums, selected, ret);
    }

public:
    int minimumDifference(vector<int>& nums) {
        N = nums.size();
        target = (double)accumulate(nums.begin(), nums.end(), 0) / 2;
        vector<int> lefthalf(nums.begin(), nums.begin() + N / 2);
        vector<int> righthalf(nums.begin() + N / 2, nums.end());
        leftsubsetsum.resize(N + 1), rightsubsetsum.resize(N + 1);
        debug(lefthalf.size());
        debug(righthalf.size());

        int selected = 0;
        subsetsum(0, lefthalf, selected, leftsubsetsum);
        selected = 0;
        subsetsum(0, righthalf, selected, rightsubsetsum);

        double min_diff = INT_MAX;
        for (int k = 0; k < leftsubsetsum.size(); k++) {
            auto& lsss = leftsubsetsum[k];
            for (auto lsum : lsss) {
                debug(lsum);

                auto& rsss = rightsubsetsum[N / 2 - k];
                auto rsum = rsss.lower_bound(target - lsum);
                if (rsum != rsss.end())
                    min_diff = min(min_diff, abs(lsum + *rsum - target));
                if (rsum != prev(rsss.end()))
                    min_diff = min(min_diff, abs(lsum + *next(rsum) - target));
                if (rsum != rsss.begin())
                    min_diff = min(min_diff, abs(lsum + *prev(rsum) - target));
            }
        }

        return min_diff * 2;
    }
};