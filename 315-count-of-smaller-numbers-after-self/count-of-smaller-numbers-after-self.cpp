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
typedef pair<int, int> pii;
#define num(pii) pii.first
#define idx(pii) pii.second

    vector<pii> arr, sorted;
    vector<int> counts;

    void merge(int s, int e) {
        int m = (s + e) / 2;
        int l = s, r = m;
        int k = l;
        int rightCount = 0;

        for (; l < m && r < e; ) {
            if (num(arr[l]) <= num(arr[r])) {
                counts[idx(arr[l])] += rightCount;

                idx(sorted[k]) = idx(arr[l]);
                num(sorted[k++]) = num(arr[l++]);
            } else {
                rightCount++;
                idx(sorted[k]) = idx(arr[r]);
                num(sorted[k++]) = num(arr[r++]);
            }
        }

        if (r == e)
            for (; l < m; ) {
                counts[idx(arr[l])] += rightCount;

                idx(sorted[k]) = idx(arr[l]);
                num(sorted[k++]) = num(arr[l++]);
            }
        else
            for (; r < e; ) {
                idx(sorted[k]) = idx(arr[r]);
                num(sorted[k++]) = num(arr[r++]);
            }

        for (int i = s; i < e; i++) {
            idx(arr[i]) = idx(sorted[i]);
            num(arr[i]) = num(sorted[i]);
        }
    }

    void sort(int s, int e) {
        if (s + 1 >= e) return;
        int m = (s + e) / 2;

        sort(s, m);
        sort(m, e);
        merge(s, e);
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        int N = nums.size();
        arr.resize(N), sorted.resize(N), counts.resize(N);
        for (int i = 0; i < N; i++)
            arr[i] = {nums[i], i};
        
        sort(0, N);
        return counts;
    }
};