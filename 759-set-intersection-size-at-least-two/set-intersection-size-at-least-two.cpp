class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(), intervals.end(), [](auto& l, auto& r) {
            if (l[1] == r[1]) return l[0] > r[0];
            return l[1] < r[1];
        });

        set<int> st;
        int p1 = -1, p2 = -1;
        for (auto& interval: intervals) {
            int s = interval[0], e = interval[1];
            if (st.size() >= 1) p2 = *st.rbegin();
            if (st.size() >= 2) p1 = *next(st.rbegin());
            
            // no overlap
            if (p2 < s) {
                st.insert(e);
                st.insert(e - 1);
            } // partial overlap  
            else if (p1 < s) {
                st.insert(e);
            }
        }

        return st.size();
    }
};