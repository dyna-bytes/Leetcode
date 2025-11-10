#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int ops = 0;
        stack<int> st;

        for (int num: nums) {
            while (st.size() && st.top() > num) {
                st.pop();
                ops++;
            }

            if (st.size() && st.top() == num)
                st.pop();

            if (num)
                st.push(num);
        }
        ops += st.size();

        return ops;
    }
};