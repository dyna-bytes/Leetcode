class Solution {
public:
    int jump(vector<int>& nums) {
        int N = nums.size();
        if (N == 1) return 0;
        vector<int> farthests(N, 0);

        int farthest = 0;
        for (int i = 0; i < N; i++) {
            farthest = max(farthest, i + nums[i]);
            farthests[i] = farthest;
        }

        int jumps = 1;
        farthest = farthests[0];
        for (int curr = 0; curr < N-1; curr++) {
            if (curr == farthest) {
                farthest = farthests[curr];
                jumps++;
            }
        }
        return jumps;
    }
};
