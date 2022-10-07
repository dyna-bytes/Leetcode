
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0) return 0;
        int N = nums.size();
        int k = 0;
        for (auto it = nums.begin(); it != nums.end(); ) {
            if (*it == val) nums.erase(it);
            else {k++; it++;}
        }

        return k;
    }
};
