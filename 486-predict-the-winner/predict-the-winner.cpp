class Solution {
    vector<int> nums;
    int f(int l, int r, int p1, int p2, bool turn) {
        if (l > r) return p1 >= p2;

        if (turn) 
            return f(l + 1 , r, p1 + nums[l], p2, !turn) || f(l, r - 1, p1 + nums[r], p2, !turn);
        else
            return f(l + 1, r, p1, p2 + nums[l], !turn) && f(l, r - 1, p1, p2 + nums[r], !turn);
    }
public:
    bool predictTheWinner(vector<int>& nums) {
        this->nums = nums;
        return f(0, nums.size() - 1, 0, 0, true);
    }
};