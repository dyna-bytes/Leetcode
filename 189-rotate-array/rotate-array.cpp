class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;

        int curr = 0;
        int start = 0;
        int num_to_rotate = nums[0];
        for (int rotate = 0; rotate < n; ) {
            int next_num_to_rotate;
            do {
                next_num_to_rotate = nums[(curr + k) % n];
                nums[(curr + k) % n] = num_to_rotate;
                num_to_rotate = next_num_to_rotate;
                curr = (curr + k) % n;
                rotate++;
            } while (curr != start);

            start++;
            curr = start;
            num_to_rotate = nums[curr];
        }
    }
};