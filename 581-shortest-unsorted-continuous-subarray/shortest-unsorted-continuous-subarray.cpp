#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do {\
    cout << #v << " is |";\
    for (auto e: v) cout << e << "|";\
    cout << endl;\
} while(0)

class Solution {
    const int INF = 1e9;
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        int rb = 0;
        int mx = -INF;
        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
            if (nums[i] < mx)
                rb = i;
        }

        int lb = n-1;
        int mn = INF;
        for (int i = n-1; i >= 0; i--) {
            mn = min(mn, nums[i]);
            if (nums[i] > mn)
                lb = i;
        }

        if (rb != 0 || lb != n-1)
            return rb - lb + 1;
        return 0;
    }
};