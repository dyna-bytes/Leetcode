class Solution {
    typedef pair<int, int> pii;
    
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int n = queries.size();
        vector<int> ans(n, -1);
        sort(intervals.begin(), intervals.end(), [](auto& left, auto& right){
            return left[1] - left[0] < right[1] - right[0];
        });

        multimap<int, int> q;
        for (int i = 0; i < n; i++) 
            q.insert({ queries[i], i });

        for (auto& inter: intervals) {
            int s = inter[0], e = inter[1];
            auto it = q.lower_bound(s);
            for (; it != q.end() && it->first <= e; it = q.erase(it)) {
                int idx = it->second;
                ans[idx] = e - s + 1;
            }
        }
        
        return ans;
    }
};