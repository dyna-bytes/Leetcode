class Solution {
    typedef long long ll;
    typedef pair<ll, ll> pll;
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> visited(n, 0);
        queue<pll> q;
        q.push({0, 0});

        while (q.size()) {
            auto [i, jumps] = q.front(); q.pop();

            for (int j = i + 1; j < n; j++) {
                if (abs(nums[i] - nums[j]) > target) continue;
                if (visited[j] >= jumps+1) continue;
                visited[j] = jumps+1;
                q.push({j, jumps+1});
            }
        }
        if (visited[n-1] == 0) return -1;
        return visited[n-1];
    }
};