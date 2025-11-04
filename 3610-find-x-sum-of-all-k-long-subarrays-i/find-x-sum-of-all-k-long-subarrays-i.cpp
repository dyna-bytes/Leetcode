class Solution {
    typedef pair<int, int> pii;
    vector<int> nums;
    int k, x;
    int xsum(int s, int e) {
        map<int, int> mp;
        for (int i = s; i < e; i++) 
            mp[nums[i]]++;
        
        set<pii> st;
        for (auto& [k, v]: mp)
            st.insert({v, k});

        int sum = 0;
        for (int i = 0; i < x && st.size(); i++) {
            auto it = st.rbegin();
            sum += (it->first * it->second);
            st.erase(--st.end());
        }
        return sum;
    }
public:
    vector<int> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        this->nums = nums;
        this->k = k;
        this->x = x;
        
        vector<int> ans(n - k + 1, 0);
        for (int i = 0; i < n - k + 1; i++)
            ans[i] = xsum(i, i+k);
        return ans;
    }
};