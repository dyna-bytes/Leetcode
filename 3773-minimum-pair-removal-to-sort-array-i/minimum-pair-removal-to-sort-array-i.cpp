#define debug(x) cout << #x << " is " << x << endl; 
#define debugVect(v) do { \
    cout << #v << " is |\t"; \
    for (auto e: v) cout << e << "\t|\t"; \
    cout << endl; \
} while (0)

class Solution {
    const int dead = -1e4;
    bool nondecreasing(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n - 1; i++) {
            while (i < n && nums[i] == dead) i++;
            if (i == n) break;

            int j = i + 1;
            while (j < n && nums[j] == dead) j++;
            if (j == n) break;

            if (nums[i] > nums[j]) 
                return false;

            i = j - 1;
        }
        return true;
    }
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0;
        while (!nondecreasing(nums)) {
            int min_sum = 1e9;
            int k = -1;
            int l = -1;
            for (int i = 0; i < n - 1; i++) {
                while (i < n && nums[i] == dead) i++;
                if (i == n) break;

                int j = i + 1;
                while (j < n && nums[j] == dead) j++;
                if (j == n) break;

                int sum = nums[i] + nums[j];
                if (min_sum > sum) {
                    min_sum = sum;
                    k = i;
                    l = j;
                }

                i = j - 1;
            }

            if (k != -1) {
                nums[k] = min_sum;
                nums[l] = dead;
            }
            cnt++;
        }
        return cnt;
    }
};