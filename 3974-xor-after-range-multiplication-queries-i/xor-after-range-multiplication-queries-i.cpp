#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define debugVec(v) do { \
    std::cout << "[Debug] ["; \
    for(int i = 0; i < ((v.size())-1); i++) std::cout << v[i] << "|"; \
    std::cout << v[((v.size())-1)] << "]\n"; \
} while(0)

class Solution {
    typedef long long ll;
    const ll MOD = 1e9 + 7;
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        for (auto& query: queries) {
            int l = query[0];
            int r = query[1];
            int k = query[2];
            ll v = query[3];

            for (int idx = l; idx <= r; idx += k)
                nums[idx] = ((ll)nums[idx] * v) % MOD;
        }

        int ans = nums[0];
        for (int i = 1; i < nums.size(); i++)
            ans ^= nums[i];
        return ans;
    }
};