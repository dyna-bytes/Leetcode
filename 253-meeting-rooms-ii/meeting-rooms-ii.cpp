class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());

        int range = 0;
        int prefix[(int)1e6 + 1];
        memset(prefix, 0, sizeof(prefix));

        for (auto& interval: intervals) {
            int s = interval[0];
            int e = interval[1];

            prefix[s]++;
            prefix[e]--;

            range = max(range, e);
        }

        int maxRooms = INT_MIN;
        for (int i = 0; i < range; i++) {
            prefix[i+1] = prefix[i] + prefix[i+1]; 
            maxRooms = max(prefix[i+1], maxRooms);
        }
        return maxRooms;
    }
};