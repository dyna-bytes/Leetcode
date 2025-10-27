class Solution {
    #define START   0
    #define END     2
    #define POINT   1 
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<vector<int>> events(intervals.size() * 2 + queries.size());

        int push = 0;
        for (auto& inter: intervals) {
            events[push++] = {inter[0], START, inter[1] - inter[0] + 1};
            events[push++] = {inter[1], END, inter[1] - inter[0] + 1};
        }

        for (int i = 0; i < queries.size(); i++) 
            events[push++] = {queries[i], POINT, i};
        
        sort(events.begin(), events.end());

        multiset<int> sizes;
        vector<int> ans(queries.size(), -1);
        for (auto& event: events) {
            if (event[1] == START) sizes.insert(event[2]);
            else if (event[1] == END) sizes.erase(sizes.find(event[2]));
            else sizes.size() ? ans[event[2]] = *sizes.begin() : -1;
        }
        return ans;
    }
};