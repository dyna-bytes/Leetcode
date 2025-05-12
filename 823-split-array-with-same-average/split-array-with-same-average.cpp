#define DBG
#ifdef DBG
#define debug(x)                                                               \
    std::cout << "[ " << __func__ << "](" << __LINE__ << ") " << #x << " is "  \
              << x << endl
#else
#define debug(x)
#endif
class Solution {
    typedef unsigned long long ull;
    void subsetsum(vector<int>& nums, vector<vector<int>>& ret) {
        int N = nums.size();
        ull totalSubsets = 1 << N;

        for (ull mask = 0; mask < totalSubsets; mask++) {
            int sum = 0, cnt = 0;
            for (int i = 0; i < N; i++) {
                if (mask & (1 << i)) {
                    sum += nums[i];
                    cnt++;
                }
            }
            ret[cnt].push_back(sum);
        }
    }
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int N = nums.size();
        int tsum = accumulate(nums.begin(), nums.end(), 0);
        vector<int> leftset(nums.begin(), nums.begin() + N / 2);
        vector<int> rightset(nums.begin() + N / 2, nums.end());

        vector<vector<int>> leftsubsetsum(N + 1);
        vector<vector<int>> rightsubsetsum(N + 1);

        subsetsum(leftset, leftsubsetsum);
        subsetsum(rightset, rightsubsetsum);

        for (auto& lsss : leftsubsetsum)
            sort(lsss.begin(), lsss.end());
        for (auto& rsss : rightsubsetsum)
            sort(rsss.begin(), rsss.end());

        auto equation = [&](int i, int j, int lsum, int rsum) -> bool {
            return N * (lsum + rsum) == tsum * (i + j);
        };

        for (int i = 0; i < leftsubsetsum.size(); i++) {
            auto& lsss = leftsubsetsum[i];
            for (int lsum : lsss) {
                for (int j = 0; j < rightsubsetsum.size(); j++) {
                    if (i + j == 0 || i + j == N) continue;
                    if ((tsum * (i + j)) % N) continue;
                    auto& rsss = rightsubsetsum[j];
                    
                    // N * (lsum + rsum) == tsum * (i + j)
                    int rsum = tsum * (i + j) / N - lsum;
                    auto it = lower_bound(rsss.begin(), rsss.end(),
                        (int)rsum);

                    if (it == rsss.end()) continue;
                    if (*it == rsum) return true;
                }
            }
        }

        return false;
    }
};