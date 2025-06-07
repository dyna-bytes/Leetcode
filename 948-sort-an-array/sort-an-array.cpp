#define DBG
#ifdef DBG
#define debug(x)                                                               \
    std::cout << "[ " << __func__ << "](" << __LINE__ << ") " << #x << " is "  \
              << x << endl
#define debugVec(v)                                                            \
    do {                                                                       \
        std::cout << "[Debug] [";                                              \
        for (int i = 0; i < ((v.size()) - 1); i++)                             \
            std::cout << v[i] << "|";                                          \
        std::cout << v[((v.size()) - 1)] << "]\n";                             \
    } while (0)
#else
#define debug(x)
#define debugVec(v)
#endif

class Solution {
    vector<int> sorted;
    void merge(vector<int>& nums, int s, int e) {
        int m = (s + e)/2;
        int l = s, r = m;
        int k = s;
        for (; l < m && r < e; ) {
            if (nums[l] < nums[r])
                sorted[k++] = nums[l++];
            else
                sorted[k++] = nums[r++];
        }

        if (l == m)
            for (; r < e; )
                sorted[k++] = nums[r++];
        else
            for (; l < m; )
                sorted[k++] = nums[l++];
    
        for (int i = s; i < e; i++)
            nums[i] = sorted[i];
    }

    void sort(vector<int>& nums, int s, int e) {
        if (s + 1 >= e) return;

        int m = (s + e)/2;
        sort(nums, s, m);
        sort(nums, m, e);
        merge(nums, s, e);
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        sorted.resize(nums.size());
        sort(nums, 0, nums.size());
        return nums;
    }
};