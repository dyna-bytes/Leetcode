class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n == 0) return true;

        sort(intervals.begin(), intervals.end());
        int prev_e = intervals[0][1];
        for (int i = 1; i < n; i++) {
            int curr_s = intervals[i][0];
            int curr_e = intervals[i][1];

            if (prev_e > curr_s) return false;
            prev_e = curr_e;
        }
        return true;
    }
};