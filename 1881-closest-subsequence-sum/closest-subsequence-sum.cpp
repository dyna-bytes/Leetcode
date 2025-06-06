#define DBG
#ifdef DBG
#define debug(x) std::cout << "[ " << __func__ << "](" << __LINE__ << ") " \
    << #x << " is " << x << endl
#else
#define debug(x)
#endif

class Solution {
    vector<int> leftsubsetsum, rightsubsetsum;
    void subsetsum(int curr, vector<int>& nums, vector<int>& stack,
                   vector<int>& ret) {
        if (curr == nums.size()) {
            int sum = 0;
            for (int n : stack)
                sum += n;
            ret.push_back(sum);
            return;
        }

        stack.push_back(nums[curr]);
        subsetsum(curr + 1, nums, stack, ret);
        stack.pop_back();

        subsetsum(curr + 1, nums, stack, ret);
    }

public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int N = nums.size();
        vector<int> leftnums(nums.begin(), nums.begin() + N / 2);
        vector<int> rightnums(nums.begin() + N / 2, nums.end());

        vector<int> stack;
        subsetsum(0, leftnums, stack, leftsubsetsum);
        stack.clear();
        subsetsum(0, rightnums, stack, rightsubsetsum);
        sort(leftsubsetsum.begin(), leftsubsetsum.end());
        sort(rightsubsetsum.begin(), rightsubsetsum.end());

        return binarySearch(goal);
    }

    int binarySearch(int goal) {
        int minDiff = INT_MAX;
        for (int x : rightsubsetsum) {
            auto it = lower_bound(leftsubsetsum.begin(),
                leftsubsetsum.end(), goal - x);
            if (it == leftsubsetsum.end()) --it;

            int y = *it;
            int diff = abs(x + y - goal);
            minDiff = min(minDiff, diff);

            if (it != leftsubsetsum.begin()) {
                y = *prev(it);
                int diff = abs(x + y - goal);
                minDiff = min(minDiff, diff);
            }

            if (it != --leftsubsetsum.end()) {
                y = *next(it);
                int diff = abs(x + y - goal);
                minDiff = min(minDiff, diff);            
            }
        }
        return minDiff;
    }

    int twoPointer(int goal) {
        int minDiff = INT_MAX;
        int l = 0, r = rightsubsetsum.size() - 1;
        while (l < leftsubsetsum.size() && r >= 0) {
            int shoot = leftsubsetsum[l] + rightsubsetsum[r];
            int diff = abs(shoot - goal);
            minDiff = min(minDiff, diff);

            if (shoot > goal) r--;
            else l++;
        }
        return minDiff;
    }
};