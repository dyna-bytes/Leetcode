#define debug(x) cout << #x << " is " << x << endl;
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int n = nums.size();

        int ans = 0;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                int t = target - nums[i] - nums[j];

                auto it = lower_bound(nums.begin() + j + 1, nums.end(), t);
                --it;
                int max_k = distance(nums.begin(), it);
                if (max_k <= j) continue;

                ans += (max_k - j);
                // j = max_k;
            }
        }

        return ans;
    }
};

/*
 * [-2, 0, 1, 3]
 * [-2, 0, 1]
 * [-2, 0, 3]
 * [-2, 1, 3]
*/