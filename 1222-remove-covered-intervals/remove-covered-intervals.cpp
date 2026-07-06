class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](vector<int>& left, vector<int>& right) {
            if (left[0] == right[0]) return left[1] >= right[1];
            return left[0] < right[0];
        });
        int prv_l = intervals[0][0], prv_r = intervals[0][1];

        int dup = 0;
        for (int i = 1; i < intervals.size(); ++i) {
            vector<int>& interval = intervals[i];
            int l = interval[0], r = interval[1];
            if (prv_l <= l && r <= prv_r)
                dup++;
            else
                prv_l = l, prv_r = r;
        }
        return intervals.size() - dup;
    }
};