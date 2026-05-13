class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> diff(2*limit + 2, 0);
        for (int i = 0; i < n/2; i++) {
            diff[2] += 2;
            diff[2*limit + 1] -= 2;
            diff[min(nums[i], nums[n-i-1]) + 1]--;
            diff[max(nums[i], nums[n-i-1]) + limit + 1]++;
            diff[nums[i] + nums[n-i-1]]--;
            diff[nums[i] + nums[n-i-1] + 1]++;
        }

        int min_moves = INT_MAX;
        int moves = 0;
        for (int i = 2; i < 2*limit + 1; i++) {
            moves += diff[i];
            min_moves = min(min_moves, moves);
        }   
        return min_moves;
    }
};