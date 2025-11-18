#define debug(x) cout << #x << " is " << x << endl;
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        int n = events.size();
        sort(events.begin(), events.end());

        int d = 0;
        int cnt = 0;
        
        priority_queue<int, vector<int>, greater<int>> pq;
        int i = 0;
        while (i < n || pq.size()) {
            while (i < n && d == events[i][0]) {
                pq.push(events[i][1]);
                i++;
            }

            while (pq.size() && d > pq.top())
                pq.pop();

            if (pq.size()) {
                pq.pop();
                cnt++;
            }
            d++;
        }

        return cnt;
    }
};