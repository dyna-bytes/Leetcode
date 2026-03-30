#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)

class Solution {
    typedef long long ll;
    const ll mod = 1e9 + 7;
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        vector<int> next_min(n); // next smallest number
       
        stack<int> st; // monoton-increasing stack
        for (int i = n-1; i >= 0; i--) {
            while (st.size() && arr[st.top()] >= arr[i])
                st.pop();

            next_min[i] = st.empty() ? n : st.top(); 
            st.push(i);
        }

        vector<int> prev_min(n); // prev smallest number
        
        st = {};
        for (int i = 0; i < n; i++) {
            while (st.size() && arr[st.top()] > arr[i])
                st.pop();

            prev_min[i] = st.empty() ? -1 : st.top();
            st.push(i); 
        }

        // debugVect(next_min);
        // debugVect(prev_min);

        ll ret = 0;
        for (int i = 0; i < n; i++) {
            ret += ((ll)arr[i] * (i - prev_min[i]) * (next_min[i] - i)) % mod;
            ret %= mod;
        }
        return ret;
    }
};