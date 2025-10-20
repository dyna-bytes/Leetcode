class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        priority_queue<int, vector<int>, greater<int>> pq;
        sort(intervals.begin(), intervals.end());

        for (auto& interval : intervals) {
            int s = interval[0];
            int e = interval[1];

            if (pq.empty() || pq.top() > s) 
                pq.push(e);
            else {
                pq.pop();
                pq.push(e);
            }
        }
        return pq.size();
    }
};