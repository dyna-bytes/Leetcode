#define debug(x) cout << #x << " is " << x << endl; 
#define debugVect(v) do { \
    cout << #v << " is |\t"; \
    for (auto e: v) cout << e << "\t|\t"; \
    cout << endl; \
} while (0)


class Solution {
public:
    int minPairSum(vector<int>& nums) {
        multiset<int> st(nums.begin(), nums.end());

        int max_sum = -1;
        while (st.size()) {
            auto mx = prev(st.end());
            auto mn = st.begin();

            int sum = *mx + *mn;
            max_sum = max(max_sum, sum);
            
            st.erase(mx);
            st.erase(mn);
        }
        return max_sum;
    }
};