// #define DEBUG
#ifdef DEBUG
#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugVect(v)
#endif

class Solution {
    typedef long long ll;
public:
    long long bowlSubarrays(vector<int>& nums) {
        int N = nums.size();
        stack<int> st; // monotone decreasing stack
        ll ans = 0;
        for (int num: nums) {
            if (st.empty() || st.top() > num) {
                st.push(num);
            } else {
                debug(num);
                int mintop = num;
                while (!st.empty() && st.top() < num) {
                    debug(st.top());
                    int curtop = st.top();
                    mintop = min(mintop, curtop);
                    st.pop();
                    if (curtop > mintop) ans++;
                    debug(ans);
                }

                if (!st.empty() && st.top() > num) {
                    debug(st.top());
                    ans++;
                }
                st.push(num);
            }
        }
        return ans;
    }
};